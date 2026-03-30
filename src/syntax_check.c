/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:58:58 by darafael          #+#    #+#             */
/*   Updated: 2026/03/30 12:30:33 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token_type type)
{
	if (type == TOK_REDIR_IN)
		return (1);
	if (type == TOK_REDIR_OUT)
		return (1);
	if (type == TOK_APPEND)
		return (1);
	if (type == TOK_HEREDOC)
		return (1);
	return (0);
}

int	check_syntax(t_token *tokens)
{
	if (!tokens)
		return (1);
	if (tokens->type == TOK_PIPE)
		return (0);
	while (tokens)
	{
		if (tokens->type == TOK_PIPE)
		{
			if (!tokens->next || tokens->next->type == TOK_PIPE)
				return (0);
		}
		if (is_redir(tokens->type))
		{
			if (!tokens->next || tokens->next->type != TOK_WORD)
				return (0);
		}
		tokens = tokens->next;
	}
	return (1);
}
