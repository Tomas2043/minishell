/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:36:56 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/03 19:18:29 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	open_and_redirect(char *filename, int flags, int target)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
		return (perror(filename), -1);
	if (dup2(fd, target) == -1)
	{
		close(fd);
		return (perror("dup2"), -1);
	}
	close(fd);
	return (0);
}

static int	apply_file_redir(t_redir *redir)
{
	if (redir->type == REDIR_IN)
		return (open_and_redirect(redir->filename, O_RDONLY, STDIN_FILENO));
	if (redir->type == REDIR_OUT)
		return (open_and_redirect(redir->filename, O_WRONLY | O_CREAT
				| O_TRUNC, STDOUT_FILENO));
	if (redir->type == REDIR_APPEND)
		return (open_and_redirect(redir->filename, O_WRONLY | O_CREAT
				| O_APPEND, STDOUT_FILENO));
	return (0);
}

int	apply_redirections(t_redir *lst, t_shell *shell)
{
	t_redir	*current;
	int		fd;

	current = lst;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
		{
			fd = current->fd;
			if (fd == -1)
				fd = handle_heredoc(current->filename, shell, current->quoted);
			if (fd == -1)
				return (-1);
			if (dup2(fd, STDIN_FILENO) == -1)
				return (close(fd), perror("dup2"), -1);
			close(fd);
			current->fd = -1;
		}
		else if (apply_file_redir(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}
