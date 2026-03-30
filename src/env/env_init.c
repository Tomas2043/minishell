/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:51:55 by toandrad          #+#    #+#             */
/*   Updated: 2026/03/30 12:16:06 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	char	*eq;
	char	*key;
	char	*value;
	t_env	*head;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		key = ft_substr(envp[i], 0, eq - envp[i]);
		value = ft_strdup(eq + 1);
		env_add_back(&head, new_env_node(key, value));
		i++;
	}
	return (head);
}
