/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_words.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 09:33:36 by darafael          #+#    #+#             */
/*   Updated: 2026/03/30 10:32:04 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_escapable_in_dquote_f(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

static char	*fill_word(const char *s, size_t *i, char *res)
{
	size_t	j;
	char	q;

	j = 0;
	q = 0;
	while (s[*i] && (q || (!is_space(s[*i]) && !is_op(s[*i]))))
	{
		if (s[*i] == '\\' && q == '"' && s[*i + 1] && is_escapable_in_dquote_f(s[*i + 1]))
		{
			res[j++] = s[*i + 1];
			(*i) += 2;
		}
		else
		{
			if (!handle_quote(s[*i], &q))
				res[j++] = s[*i];
			(*i)++;
		}
	}
	res[j] = '\0';
	return (res);
}

static char	*get_word(const char *s, size_t *i)
{
	char	*res;
	size_t	len;

	len = word_len(s, *i);
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	return (fill_word(s, i, res));
}

static int	add_token(char **arr, size_t *k, const char *s, size_t *i)
{
	if (is_op(s[*i]))
		arr[*k] = get_op(s, i);
	else
		arr[*k] = get_word(s, i);
	if (!arr[*k])
		return (0);
	(*k)++;
	return (1);
}

char	**ms_tokenize(const char *s)
{
	char	**arr;
	size_t	count;
	size_t	i;
	size_t	k;

	if (!s)
		return (NULL);
	count = count_tokens(s);
	if (*s && count == 0)
		return (NULL);
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	k = 0;
	arr[0] = NULL;
	while (s[i])
	{
		skip_spaces(s, &i);
		if (s[i] && !add_token(arr, &k, s, &i))
			return (free_split(arr), NULL);
		arr[k] = NULL;
	}
	return (arr);
}
