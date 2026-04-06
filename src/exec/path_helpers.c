/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 11:57:15 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/06 12:12:13 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_in_paths(char **paths, char *command)
{
	int		i;
	char	*tmp;
	char	*slash;

	i = 0;
	while (paths[i] != NULL)
	{
		slash = ft_strjoin(paths[i], "/");
		free(paths[i]);
		paths[i] = slash;
		tmp = ft_strjoin(paths[i], command);
		if (access(tmp, X_OK) == 0)
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
