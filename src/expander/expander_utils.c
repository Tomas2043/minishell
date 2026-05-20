/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 13:23:00 by darafael          #+#    #+#             */
/*   Updated: 2026/05/20 13:23:04 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
