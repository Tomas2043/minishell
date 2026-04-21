/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomas <tomas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:14:41 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/17 22:53:04 by tomas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	pid_t	pid;

	path = resolve_path(cmd->argv[0], shell->env);
	if (path == NULL)
	{
		ft_putendl_fd("minishell: command not found", 2);
		shell->exit_status = 127;
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		free(path);
		perror("Fork");
		return ;
	}
	else if (pid == 0)
		child_execute(cmd, path, shell);
	else
	{
		wait_child(pid, shell);
		free(path);
	}
}

static void	execute_builtin(t_cmd *cmd, t_shell *shell, int builtin)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	apply_redirections(cmd->redirs, shell);
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
	else if (builtin == 7)
		builtin_exit(cmd, shell);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	execute(t_cmd *cmd, t_shell *shell)
{
	int	builtin;

	if (cmd->next)
	{
		execute_pipeline(cmd, shell);
		return ;
	}
	builtin = is_builtin(cmd);
	if (builtin)
		execute_builtin(cmd, shell, builtin);
	else
		execute_external(cmd, shell);
}
