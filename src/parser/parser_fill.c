/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_fill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:58:21 by darafael          #+#    #+#             */
/*   Updated: 2026/04/27 09:58:24 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	get_redir_type(t_token_type type)
{
	if (type == TOK_REDIR_IN)
		return (REDIR_IN);
	if (type == TOK_REDIR_OUT)
		return (REDIR_OUT);
	if (type == TOK_APPEND)
		return (REDIR_APPEND);
	if (type == TOK_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

static char	*strip_quotes(char *s)
{
	char	*result;
	int		i;
	int		j;

	result = malloc(ft_strlen(s) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\'' && s[i] != '"' && s[i] != '\\')
			result[j++] = s[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

static int	count_cmd_words(t_token *tok)
{
	int	count;

	count = 0;
	while (tok && tok->type != TOK_PIPE)
	{
		if (get_redir_type(tok->type) != -1)
		{
			tok = tok->next;
			if (tok)
				tok = tok->next;
		}
		else
		{
			count++;
			tok = tok->next;
		}
	}
	return (count);
}

static int	parse_redir(t_cmd *cmd, t_token **tok)
{
	t_redir_type	type;
	t_redir			*redir;
	char			*filename;
	int				quoted;

	type = (t_redir_type)get_redir_type((*tok)->type);
	*tok = (*tok)->next;
	if (!*tok)
		return (0);
	quoted = (type == REDIR_HEREDOC
			&& (ft_strchr((*tok)->value, '\'')
				|| ft_strchr((*tok)->value, '"')
				|| ft_strchr((*tok)->value, '\\')));
	if (type == REDIR_HEREDOC)
		filename = strip_quotes((*tok)->value);
	else
		filename = ft_strdup((*tok)->value);
	if (!filename)
		return (0);
	redir = new_redir(type, filename, quoted);
	free(filename);
	if (!redir)
		return (0);
	redir_add_back(&cmd->redirs, redir);
	*tok = (*tok)->next;
	return (1);
}

int	fill_cmd(t_cmd *cmd, t_token **tok)
{
	int	count;
	int	i;

	count = count_cmd_words(*tok);
	cmd->argv = ft_calloc(count + 1, sizeof(char *));
	if (!cmd->argv)
		return (0);
	i = 0;
	while (*tok && (*tok)->type != TOK_PIPE)
	{
		if (get_redir_type((*tok)->type) != -1)
		{
			if (!parse_redir(cmd, tok))
				return (0);
		}
		else
		{
			cmd->argv[i++] = ft_strdup((*tok)->value);
			if (!cmd->argv[i - 1])
				return (0);
			*tok = (*tok)->next;
		}
	}
	return (1);
}
