/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:32:00 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/27 12:53:56 by toandrad         ###   ########.fr       */
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
		return (ft_strdup(path));
	}
	else if (ft_strcmp(cmd->argv[1], "-") == 0)
	{
		path = get_env(shell->env, "OLDPWD");
		if (!path)
			return (ft_putendl_fd("minishell: cd: OLDPWD not set", 2),
				NULL);
		printf("%s\n", path);
		return (ft_strdup(path));
	}
	return (ft_strdup(cmd->argv[1]));
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
	free(path);
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
	if (is_valid_identifier(key))
		set_env(&shell->env, key, value);
	else
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(key, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	free(key);
	free(value);
}

void	builtin_export(t_cmd *cmd, t_shell *shell)
{
	char	**array;
	int		i;

	i = 1;
	if (cmd->argv[1] == NULL)
	{
		array = env_to_declare_array(shell->env);
		sort_env_array(array, count_env_size(shell->env));
		i = -1;
		while (array[++i])
			ft_putendl_fd(array[i], 1);
		free_env_array(array);
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
		if (is_valid_identifier(cmd->argv[i]))
			remove_env(&shell->env, cmd->argv[i]);
		else
		{
			ft_putstr_fd("minishell: unset: '", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
}
