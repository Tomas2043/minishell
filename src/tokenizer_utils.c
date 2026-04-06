/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 09:56:33 by darafael          #+#    #+#             */
/*   Updated: 2026/04/06 11:38:54 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote(char c, char *q)
{
	if (*q == 0 && (c == '\'' || c == '"'))
	{
		*q = c;
		return (1);
	}
	if (*q != 0 && c == *q)
	{
		*q = 0;
		return (1);
	}
	return (0);
}

int	escapable_quote(char c)
{
	return (c == '"' || c == '\\' || c == '$' || c == '`');
}

void	skip_word_chars(const char *s, size_t *i, char *q)
{
	while (s[*i] && (*q || (!is_space(s[*i]) && !is_op(s[*i]))))
	{
		if (s[*i] == '\\' && *q == '"' && s[*i + 1]
			&& escapable_quote(s[*i + 1]))
		{
			(*i) += 2;
		}
		else
		{
			handle_quote(s[*i], q);
			(*i)++;
		}
	}
}

void	skip_token_op(const char *s, size_t *i)
{
	if (s[*i] == '|')
		(*i)++;
	else if ((s[*i] == '<' || s[*i] == '>') && s[*i + 1] == s[*i])
		*i += 2;
	else if (s[*i] == '<' || s[*i] == '>')
		(*i)++;
}

size_t	word_len(const char *s, size_t i)
{
	size_t	len;
	char	q;

	len = 0;
	q = 0;
	while (s[i] && (q || (!is_space(s[i]) && !is_op(s[i]))))
	{
		if (s[i] == '\\' && q == '"' && s[i + 1] && escapable_quote(s[i + 1]))
		{
			len++;
			i += 2;
		}
		else
		{
			if (!handle_quote(s[i], &q))
				len++;
			i++;
		}
	}
	return (len);
}
