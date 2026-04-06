/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 09:42:44 by darafael          #+#    #+#             */
/*   Updated: 2026/04/06 13:33:45 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static size_t	count_word_tokens(const char *s, size_t *i)
{
	char	q;

	q = 0;
	skip_word_chars(s, i, &q);
	if (q != 0)
		return (0);
	return (1);
}

static int	count_one_token(const char *s, size_t *i)
{
	if (is_op(s[*i]))
		skip_token_op(s, i);
	else if (!count_word_tokens(s, i))
		return (0);
	return (1);
}

static void	init_count_vars(size_t *i, size_t *count)
{
	*i = 0;
	*count = 0;
}

size_t	count_tokens(const char *s)
{
	size_t	i;
	size_t	count;

	init_count_vars(&i, &count);
	while (s[i])
	{
		skip_spaces(s, &i);
		if (!s[i])
			break ;
		count++;
		if (!count_one_token(s, &i))
			return (0);
	}
	return (count);
}
