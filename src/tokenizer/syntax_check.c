/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:58:58 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 12:35:09 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char	*get_bad_token(t_token *tok)
{
	if (!tok || !tok->next)
		return ("newline");
	if (tok->next->type == TOK_PIPE)
		return ("|");
	if (tok->next->type == TOK_REDIR_OUT)
		return (">");
	if (tok->next->type == TOK_APPEND)
		return (">>");
	if (tok->next->type == TOK_REDIR_IN)
		return ("<");
	return ("newline");
}

char	find_unclosed_quote(const char *line)
{
	char	q;
	int		i;

	q = 0;
	i = 0;
	while (line[i])
	{
		if (!q && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		i++;
	}
	return (q);
}

static int	check_token(t_token *t, char **bad)
{
	int	redir;

	redir = (t->type == TOK_REDIR_IN || t->type == TOK_REDIR_OUT
			|| t->type == TOK_APPEND || t->type == TOK_HEREDOC);
	if (t->type == TOK_PIPE)
	{
		if (!t->next || t->next->type == TOK_PIPE)
		{
			*bad = (char *)get_bad_token(t);
			return (0);
		}
	}
	if (redir)
	{
		if (!t->next || t->next->type != TOK_WORD)
		{
			*bad = (char *)get_bad_token(t);
			return (0);
		}
	}
	return (1);
}

int	check_syntax(t_token *tokens, char **bad)
{
	t_token	*t;

	*bad = NULL;
	if (!tokens)
		return (1);
	if (tokens->type == TOK_PIPE)
	{
		*bad = "|";
		return (0);
	}
	t = tokens;
	while (t)
	{
		if (!check_token(t, bad))
			return (0);
		t = t->next;
	}
	return (1);
}

void	print_syntax_error(char *bad)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (bad)
		ft_putstr_fd(bad, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putendl_fd("'", 2);
}
