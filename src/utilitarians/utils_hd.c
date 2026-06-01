/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_hd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 00:00:00 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 13:27:14 by darafael         ###   ########.fr       */
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

void	process_hd_lines(t_shell *shell)
{
	char	*extra;

	while (shell->hd_input && *shell->hd_input)
	{
		extra = next_hd_line(shell);
		if (extra && *extra)
		{
			add_history(extra);
			handle_line(&extra, shell);
		}
		free(extra);
	}
	free(shell->hd_input);
	shell->hd_input = NULL;
}

void	process_input_line(char *line, t_shell *shell)
{
	char		*orig;
	HIST_ENTRY	*old;

	if (!isatty(STDIN_FILENO))
	{
		line = get_full_history_line(line);
		split_hd_input(line, shell);
	}
	shell->hd_cmd = line;
	add_history(line);
	shell->hd_hist_idx = history_length - 1;
	orig = line;
	handle_line(&line, shell);
	if (line && line != orig)
	{
		old = replace_history_entry(shell->hd_hist_idx, line, NULL);
		if (old)
			free_history_entry(old);
	}
	free(shell->hd_hist);
	shell->hd_hist = NULL;
	shell->hd_cmd = NULL;
	process_hd_lines(shell);
	free(line);
}
