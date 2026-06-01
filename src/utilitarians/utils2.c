/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 13:04:21 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 13:52:22 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	restore_signals(void)
{
	rl_event_hook = NULL;
	setup_signals();
}

char	*cancel_cont(char *line, char *cont, t_shell *shell)
{
	if (!cont)
		shell->running = 0;
	free(line);
	free(cont);
	restore_signals();
	return (NULL);
}

char	*append_cont_line(char *line, char *cont)
{
	char	*tmp;

	tmp = ft_strjoin(line, " ");
	free(line);
	line = ft_strjoin(tmp, cont);
	free(tmp);
	free(cont);
	return (line);
}

int	digit_overflow(char *str)
{
	int	i;
	int	sig;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	sig = 0;
	while (ft_isdigit(str[i + sig]))
		sig++;
	if (sig > 19)
		return (1);
	if (sig < 19)
		return (0);
	return (ft_strncmp(str + i, "9223372036854775807", 19) > 0);
}
