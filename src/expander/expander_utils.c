/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 11:21:07 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/20 11:26:12 by toandrad         ###   ########.fr       */
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
