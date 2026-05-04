/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 09:58:09 by darafael          #+#    #+#             */
/*   Updated: 2026/05/04 11:36:56 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*new_redir(t_redir_type type, char *filename, int quoted)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->filename = ft_strdup(filename);
	if (!redir->filename)
	{
		free(redir);
		return (NULL);
	}
	redir->quoted = quoted;
	redir->fd = -1;
	redir->next = NULL;
	return (redir);
}

void	redir_add_back(t_redir **head, t_redir *node)
{
	t_redir	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

static void	cmd_add_back(t_cmd **head, t_cmd *node)
{
	t_cmd	*tmp;

	if (!head || !node)
		return ;
	if (!*head)
	{
		*head = node;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*head;
	t_cmd	*cmd;
	t_token	*tok;

	head = NULL;
	tok = tokens;
	while (tok)
	{
		cmd = new_cmd();
		if (!cmd)
			return (free_cmd_list(head), NULL);
		if (!fill_cmd(cmd, &tok))
		{
			free_cmd(cmd);
			free_cmd_list(head);
			return (NULL);
		}
		cmd_add_back(&head, cmd);
		if (tok && tok->type == TOK_PIPE)
			tok = tok->next;
	}
	return (head);
}
