/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 14:47:01 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/06 19:57:18 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	run_builtin(t_cmd *cmd, t_shell *shell, int builtin)
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
	else if (builtin == 7)
		builtin_exit(cmd, shell);
}

static void	child_pipeline(t_cmd *current, t_pipe_info *info, t_shell *shell)
{
	int	j;
	int	builtin;

	j = 0;
	if (info->i < info->n - 1)
		dup2(info->pipes[info->i][1], STDOUT_FILENO);
	if (info->i > 0)
		dup2(info->pipes[info->i - 1][0], STDIN_FILENO);
	while (j < info->n - 1)
	{
		close(info->pipes[j][0]);
		close(info->pipes[j][1]);
		j++;
	}
	if (apply_redirections(current->redirs, shell) == -1)
		exit(1);
	if (!current->argv || !current->argv[0])
		exit(0);
	builtin = is_builtin(current);
	if (builtin)
		return (run_builtin(current, shell, builtin), exit(shell->exit_status),
			(void)0);
	else
		pipeline_execute_external(current, shell);
}

static void	wait_pipeline(pid_t *pids, int **pipes, int n, t_shell *shell)
{
	int	i;
	int	status;

	close_pipe_fds(pipes, n);
	i = 0;
	while (i < n)
	{
		setup_wait_signals();
		waitpid(pids[i], &status, 0);
		setup_signals();
		if (i == n - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (free(pids), free_pipes(pipes, n - 1));
}

static void	fork_pipeline(t_cmd *cmd, int **pipes, int n, t_shell *shell)
{
	t_pipe_info	info;
	pid_t		*pids;
	t_cmd		*current;
	int			i;

	i = 0;
	info.n = n;
	info.pipes = pipes;
	current = cmd;
	pids = malloc(sizeof(pid_t) * n);
	if (!pids)
		return ;
	while (i < n)
	{
		info.i = i;
		pids[i] = fork();
		if (pids[i] == -1)
			return (free_pipes(pipes, n - 1), free(pids));
		else if (pids[i] == 0)
			child_pipeline(current, &info, shell);
		current = current->next;
		i++;
	}
	wait_pipeline(pids, pipes, n, shell);
}

void	execute_pipeline(t_cmd *cmd, t_shell *shell)
{
	int	**pipes;
	int	n;
	int	i;

	if (prepare_heredocs(cmd, shell) == -1)
		return ;
	n = count_cmds(cmd);
	pipes = malloc(sizeof(int *) * (n - 1));
	if (!pipes)
		return (close_prepared_heredocs(cmd));
	i = 0;
	while (i < n - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (free_pipes(pipes, i), close_prepared_heredocs(cmd));
		if (pipe(pipes[i]) == -1)
			return (free_pipes(pipes, i + 1), close_prepared_heredocs(cmd));
		i++;
	}
	fork_pipeline(cmd, pipes, n, shell);
	close_prepared_heredocs(cmd);
}
