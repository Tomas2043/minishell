/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 14:36:56 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/27 12:11:26 by darafael         ###   ########.fr       */
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

static void	write_heredoc_line(char *line, t_shell *shell, int fd, int quoted)
{
	char	*expanded;

	if (!quoted)
		expanded = expand_string(line, shell);
	else
		expanded = ft_strdup(line);
	write(fd, expanded, ft_strlen(expanded));
	write(fd, "\n", 1);
	free(expanded);
	free(line);
}

int	handle_heredoc(char *delimiter, t_shell *shell, int quoted)
{
	int		fd[2];
	char	*line;

	pipe(fd);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(line, shell, fd[1], quoted);
	}
	close(fd[1]);
	return (fd[0]);
}

void	apply_redirections(t_redir *lst, t_shell *shell)
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
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		current = current->next;
	}
}
