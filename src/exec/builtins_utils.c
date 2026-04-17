/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 11:31:36 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/17 11:50:46 by toandrad         ###   ########.fr       */
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
