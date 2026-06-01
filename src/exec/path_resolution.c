/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolution.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:28:48 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/27 12:45:37 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_in_paths(char **paths, char *command)
{
	int			i;
	char		*tmp;
	char		*slash;
	struct stat	st;

	i = 0;
	while (paths[i] != NULL)
	{
		slash = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = slash;
		tmp = ft_strjoin(paths[i], command);
		if (access(tmp, X_OK) == 0 && stat(tmp, &st) == 0
			&& !S_ISDIR(st.st_mode))
		{
			free_env_array(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_env_array(paths);
	return (NULL);
}

char	*resolve_path(char *command, t_env *lst)
{
	char	**paths;
	char	*path;

	if (!command || command[0] == '\0')
		return (NULL);
	if (ft_strchr(command, '/'))
	{
		if (access(command, F_OK) != 0)
			return (NULL);
		return (ft_strdup(command));
	}
	path = get_env(lst, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	return (search_in_paths(paths, command));
}
