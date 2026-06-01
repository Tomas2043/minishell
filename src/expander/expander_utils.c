/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:23:00 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 11:01:11 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_quoted_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\'' && str[i] != '"')
			return (0);
		i++;
	}
	return (i > 0);
}

void	compact_empty_args(char **argv, int *keep)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (argv[i])
	{
		if (argv[i][0] != '\0' || keep[i])
			argv[j++] = argv[i];
		else
			free(argv[i]);
		i++;
	}
	argv[j] = NULL;
}

int	update_quote_state(char c, int *sq, int *dq)
{
	if (c == '\'' && !*dq)
	{
		*sq = !*sq;
		return (1);
	}
	if (c == '"' && !*sq)
	{
		*dq = !*dq;
		return (1);
	}
	return (0);
}
