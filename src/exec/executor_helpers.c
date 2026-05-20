/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:46:02 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/20 14:49:17 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	wait_child(pid_t pid, t_shell *shell)
{
	int	status;

	setup_wait_signals();
	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
			return (setup_signals());
	}
	setup_signals();
	if (WIFEXITED(status))
		shell->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->exit_status = 128 + WTERMSIG(status);
}

void	child_execute(t_cmd *cmd, char *path, t_shell *shell)
{
	char	**env;

	reset_signals();
	if (apply_redirections(cmd->redirs, shell) == -1)
		exit(1);
	env = env_to_array(shell->env);
	execve(path, cmd->argv, env);
	perror(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	pipeline_execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	**env;

	reset_signals();
	path = resolve_path(cmd->argv[0], shell->env);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	env = env_to_array(shell->env);
	execve(path, cmd->argv, env);
	perror(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
