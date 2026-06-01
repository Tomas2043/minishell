/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 13:14:41 by toandrad          #+#    #+#             */
/*   Updated: 2026/06/01 11:12:21 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	execute_external(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	pid_t	pid;

	if (prepare_heredocs(cmd, shell) == -1)
		return ;
	path = resolve_path(cmd->argv[0], shell->env);
	if (!path)
		return (print_not_found_error(cmd->argv[0]),
			shell->exit_status = 127, close_prepared_heredocs(cmd));
	pid = fork();
	if (pid == -1)
		return (free(path), perror("Fork"), close_prepared_heredocs(cmd));
	else if (pid == 0)
		child_execute(cmd, path, shell);
	else
	{
		wait_child(pid, shell);
		free(path);
	}
	close_prepared_heredocs(cmd);
}

static void	restore_close(int saved_stdout, int saved_stdin)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

static void	execute_builtin(t_cmd *cmd, t_shell *shell, int builtin)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	shell->exit_status = 0;
	if (apply_redirections(cmd->redirs, shell) == -1)
		return (shell->exit_status = 1,
			restore_close(saved_stdout, saved_stdin));
	if (builtin == 7)
	{
		restore_close(saved_stdout, saved_stdin);
		builtin_exit(cmd, shell);
		return ;
	}
	dispatch_builtin(cmd, shell, builtin);
	restore_close(saved_stdout, saved_stdin);
}

static void	execute_empty_command(t_cmd *cmd, t_shell *shell)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	shell->exit_status = 0;
	if (apply_redirections(cmd->redirs, shell) == -1)
		shell->exit_status = 1;
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
	if (!cmd->argv || !cmd->argv[0])
	{
		execute_empty_command(cmd, shell);
		return ;
	}
	builtin = is_builtin(cmd);
	if (builtin)
		execute_builtin(cmd, shell, builtin);
	else
		execute_external(cmd, shell);
}
