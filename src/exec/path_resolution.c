/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:28:48 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/06 12:12:41 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*resolve_path(char *command, t_env *lst)
{
	char	**paths;
	char	*path;

	if (ft_strchr(command, '/'))
	{
		if (access(command, X_OK) == 0)
			return (command);
		return (NULL);
	}
	path = get_env(lst, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (search_in_paths(paths, command));
}
