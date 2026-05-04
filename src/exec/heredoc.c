/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 18:30:48 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/03 22:30:50 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	heredoc_interrupted(t_heredoc *hd, t_shell *shell)
{
	dup2(hd->saved_stdin, STDIN_FILENO);
	close(hd->saved_stdin);
	tcsetattr(STDIN_FILENO, TCSANOW, &hd->saved_term);
	rl_done = 0;
	close(hd->fd[0]);
	close(hd->fd[1]);
	shell->exit_status = 130;
	g_signal = 0;
	setup_signals();
	return (-1);
}

static int	heredoc_loop(char *delim, t_shell *shell, int quoted,
t_heredoc *hd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (g_signal == SIGINT)
			return (free(line), heredoc_interrupted(hd, shell));
		if (!line)
		{
			ft_putendl_fd("warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strcmp(line, delim) == 0)
		{
			free(line);
			break ;
		}
		write_heredoc_line(line, shell, hd->fd[1], quoted);
	}
	return (0);
}

int	handle_heredoc(char *delimiter, t_shell *shell, int quoted)
{
	t_heredoc	hd;

	if (pipe(hd.fd) == -1)
		return (perror("pipe"), -1);
	hd.saved_stdin = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &hd.saved_term);
	setup_heredoc_signals();
	if (heredoc_loop(delimiter, shell, quoted, &hd) == -1)
		return (-1);
	return (close(hd.saved_stdin), close(hd.fd[1]), setup_signals(), hd.fd[0]);
}

void	setup_heredoc_signals(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_heredoc_sigint;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
