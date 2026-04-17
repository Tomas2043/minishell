/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:31:36 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/17 13:59:20 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_n_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1])
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

int	is_valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (ft_isalpha(str[i]) || str[i] == '_')
	{
		i++;
		while (str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}

void	sort_env_array(char **array, int size)
{
	int		i;
	int		j;
	char	*tmp;

	j = 0;
	while (j < size)
	{
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
			}
			i++;
		}
		j++;
	}
}

char	**env_to_declare_array(t_env *lst)
{
	t_env	*current;
	int		env_size;
	char	**res;
	char	*tmp;
	int		i;

	env_size = count_env_size(lst);
	res = malloc(sizeof(char **) * (env_size + 1));
	i = 0;
	current = lst;
	while (current)
	{
		tmp = ft_strjoin("declare -x ", current->key);
		res[i] = ft_strjoin(tmp, "=\"");
		free(tmp);
		tmp = ft_strjoin(res[i], current->value);
		free(res[i]);
		res[i] = ft_strjoin(tmp, "\"");
		free(tmp);
		i++;
		current = current->next;
	}
	res[env_size] = NULL;
	return (res);
}
