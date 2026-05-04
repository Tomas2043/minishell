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

void	open_and_redirect(char *filename, int flags, int target)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		exit(1);
	}
	dup2(fd, target);
	close(fd);
}

int	apply_redirections(t_redir *lst, t_shell *shell)
{
	t_redir	*current;
	int		fd;

	current = lst;
	while (current)
	{
		if (current->type == REDIR_IN)
			open_and_redirect(current->filename, O_RDONLY, STDIN_FILENO);
		else if (current->type == REDIR_OUT)
			open_and_redirect(current->filename, O_WRONLY | O_CREAT
				| O_TRUNC, STDOUT_FILENO);
		else if (current->type == REDIR_APPEND)
			open_and_redirect(current->filename, O_WRONLY | O_CREAT
				| O_APPEND, STDOUT_FILENO);
		else if (current->type == REDIR_HEREDOC)
		{
			fd = handle_heredoc(current->filename, shell, current->quoted);
			if (fd == -1)
				return (-1);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		current = current->next;
	}
	return (0);
}
