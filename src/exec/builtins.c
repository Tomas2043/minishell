/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 12:59:56 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/17 13:48:38 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_cmd *cmd)
{
	if (ft_strcmp(cmd->argv[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->argv[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd->argv[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd->argv[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cmd->argv[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd->argv[0], "env") == 0)
		return (6);
	else if (ft_strcmp(cmd->argv[0], "exit") == 0)
		return (7);
	else
		return (0);
}

void	builtin_env(t_shell *shell)
{
	t_env	*current;

	current = shell->env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

void	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("Getcwd");
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
}

void	builtin_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	if (!cmd->argv[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (is_n_flag(cmd->argv[1]))
	{
		newline = 0;
		i = 2;
	}
	while (cmd->argv[i])
	{
		printf("%s", cmd->argv[i]);
		if (cmd->argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	printf("exit\n");
	if (!cmd->argv[1])
		exit(shell->exit_status);
	else if (!ft_isnumeric(cmd->argv[1])
		|| ft_strlen(cmd->argv[1]) - (cmd->argv[1][0] == '-') > 19)
	{
		ft_putendl_fd("minishell: exit: numeric argument required", 2);
		exit(255);
	}
	else if (cmd->argv[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		shell->exit_status = 1;
		return ;
	}
	else
		exit(ft_atoi(cmd->argv[1]));
}
