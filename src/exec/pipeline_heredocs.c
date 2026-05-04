/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_heredocs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 11:39:24 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/04 11:44:26 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_prepared_heredocs(t_cmd *cmd)
{
	t_redir	*redir;

	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC && redir->fd != -1)
			{
				close(redir->fd);
				redir->fd = -1;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

int	prepare_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*head;
	t_redir	*redir;

	head = cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->type == REDIR_HEREDOC)
			{
				redir->fd = handle_heredoc(redir->filename, shell,
						redir->quoted);
				if (redir->fd == -1)
					return (close_prepared_heredocs(head), -1);
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
