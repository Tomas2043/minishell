/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_replay.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by darafael          #+#    #+#             */
/*   Updated: 2026/05/27 00:00:00 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	split_hd_input(char *line, t_shell *shell)
{
	char	*nl;

	nl = ft_strchr(line, '\n');
	if (!nl)
		return ;
	shell->hd_input = ft_strdup(nl + 1);
	*nl = '\0';
}

char	*next_hd_line(t_shell *shell)
{
	char	*nl;
	char	*line;
	char	*rest;

	if (!shell->hd_input || !*shell->hd_input)
		return (NULL);
	nl = ft_strchr(shell->hd_input, '\n');
	if (nl)
	{
		line = ft_substr(shell->hd_input, 0, nl - shell->hd_input);
		rest = ft_strdup(nl + 1);
		free(shell->hd_input);
		shell->hd_input = rest;
	}
	else
	{
		line = ft_strdup(shell->hd_input);
		free(shell->hd_input);
		shell->hd_input = NULL;
	}
	return (line);
}

char	*hd_readline(t_shell *shell)
{
	if (shell->hd_input)
		return (next_hd_line(shell));
	return (readline("> "));
}
