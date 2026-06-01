/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:46:02 by toandrad          #+#    #+#             */
/*   Updated: 2026/06/01 11:12:21 by darafael         ###   ########.fr       */
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
	char		**env;
	struct stat	st;

	reset_signals();
	if (apply_redirections(cmd->redirs, shell) == -1)
		exit(1);
	env = env_to_array(shell->env);
	execve(path, cmd->argv, env);
	if (errno == EACCES && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": Is a directory", 2);
		exit(126);
	}
	perror(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}

void	dispatch_builtin(t_cmd *cmd, t_shell *shell, int builtin)
{
	if (builtin == 1)
		builtin_echo(cmd);
	else if (builtin == 2)
		builtin_cd(cmd, shell);
	else if (builtin == 3)
		builtin_pwd();
	else if (builtin == 4)
		builtin_export(cmd, shell);
	else if (builtin == 5)
		builtin_unset(cmd, shell);
	else if (builtin == 6)
		builtin_env(shell);
}

void	print_not_found_error(char *cmd)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd[0] == '\0')
		ft_putstr_fd("''", 2);
	else
		ft_putstr_fd(cmd, 2);
	if (ft_strchr(cmd, '/'))
		ft_putendl_fd(": No such file or directory", 2);
	else
		ft_putendl_fd(": command not found", 2);
}

void	pipeline_execute_external(t_cmd *cmd, t_shell *shell)
{
	char		*path;
	char		**env;
	struct stat	st;

	reset_signals();
	path = resolve_path(cmd->argv[0], shell->env);
	if (!path)
		return (print_not_found_error(cmd->argv[0]), exit(127));
	env = env_to_array(shell->env);
	execve(path, cmd->argv, env);
	if (errno == EACCES && stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(" : Is a directory", 2);
		exit(126);
	}
	perror(path);
	if (errno == ENOENT)
		exit(127);
	exit(126);
}
