/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:22:45 by toandrad          #+#    #+#             */
/*   Updated: 2026/03/30 14:47:00 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*get_env(t_env *lst, char *key)
{
	char	*path;

	path = NULL;
	while (lst)
	{
		if (ft_strcmp(lst->key, key) == 0)
		{
			path = lst->value;
			break ;
		}
		lst = lst->next;
	}
	return (path);
}

void	set_env(t_env **lst, char *key, char *value)
{
	t_env	*current;
	int		found;

	current = *lst;
	found = 0;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = value;
			found = 1;
			break ;
		}
		current = current->next;
	}
	if (!found)
		env_add_back(lst, new_env_node(key, value));
}

void	remove_env(t_env **lst, char *key)
{
	t_env	*current;
	t_env	*prev;
	
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev == NULL)
				*lst = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

char	**env_to_array(t_env *lst)
{
	t_env	*current;
	int		env_size;
	char	**result;
	char	*tmp;
	int		i;

	env_size = count_env_size(lst);
	result = malloc(sizeof(char **) * (env_size + 1));
	i = 0;
	current = lst;
	while (current)
	{
		tmp = ft_strjoin(current->key, "=");
		result[i] = ft_strjoin(tmp, current->value);
		free(tmp);
		i++;
		current = current->next;
	}
	result[env_size] = NULL;
	return (result);
}
