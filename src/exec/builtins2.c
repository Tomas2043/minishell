/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:32:00 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/16 11:39:39 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_cd_path(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->argv[1])
	{
		path = get_env(shell->env, "HOME");
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (NULL);
		}
		return (path);
	}
	return (cmd->argv[1]);
}

void	builtin_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = get_cd_path(cmd, shell);
	if (!path)
		return ;
	oldpwd = getcwd(NULL, 0);
	set_env(&shell->env, "OLDPWD", oldpwd);
	free(oldpwd);
	if (chdir(path) == -1)
		perror(path);
	else
	{
		pwd = getcwd(NULL, 0);
		set_env(&shell->env, "PWD", pwd);
		free(pwd);
	}
}

static void	export_var(char *arg, t_shell *shell)
{
	char	*eq;
	char	*key;
	char	*value;

	eq = ft_strchr(arg, '=');
	if (!eq)
		return ;
	key = ft_substr(arg, 0, eq - arg);
	value = ft_strdup(eq + 1);
	set_env(&shell->env, key, value);
	free(key);
	free(value);
}

void	builtin_export(t_cmd *cmd, t_shell *shell)
{
	t_env	*current;
	int		i;

	current = shell->env;
	i = 1;
	if (cmd->argv[1] == NULL)
	{
		while (current)
		{
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
			current = current->next;
		}
	}
	else
	{
		while (cmd->argv[i])
		{
			export_var(cmd->argv[i], shell);
			i++;
		}
	}
}

void	builtin_unset(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		remove_env(&shell->env, cmd->argv[i]);
		i++;
	}
}
