/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 14:32:00 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/08 14:52:50 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	builtins_cd(t_cmd *cmd, t_shell *shell)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	if (!cmd->argv[1])
	{
		path = get_env(shell->env, "HOME");
		if (!path)
			ft_putendl_fd("minishell: cd: HOME not set", 2);
	}
	else
		path = cmd->argv[1];
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
