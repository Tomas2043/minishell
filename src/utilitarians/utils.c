/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:34:14 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 12:57:48 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	append_hd_hist(t_shell *shell, char *line)
{
	char	*with_nl;
	char	*tmp;

	with_nl = ft_strjoin("\n", line);
	if (!with_nl)
		return ;
	if (shell->hd_hist)
		tmp = ft_strjoin(shell->hd_hist, with_nl);
	else
		tmp = ft_strdup(with_nl);
	free(with_nl);
	free(shell->hd_hist);
	shell->hd_hist = tmp;
}

void	update_hd_history(t_shell *shell)
{
	char		*full;
	char		*with_nl;
	HIST_ENTRY	*old;

	if (!shell->hd_cmd || !shell->hd_hist)
		return ;
	full = ft_strjoin(shell->hd_cmd, shell->hd_hist);
	if (!full)
		return ;
	with_nl = ft_strjoin(full, "\n");
	free(full);
	if (!with_nl)
		return ;
	old = replace_history_entry(shell->hd_hist_idx, with_nl, NULL);
	free(with_nl);
	if (old)
		free_history_entry(old);
}

char	*get_full_history_line(char *line)
{
	HIST_ENTRY	*he;
	char		*full;

	he = current_history();
	if (!he || !he->line)
		return (line);
	if (ft_strchr(line, '\n'))
		return (line);
	if (ft_strncmp(he->line, line, ft_strlen(line)) != 0
		|| he->line[ft_strlen(line)] != '\n')
		return (line);
	full = ft_strdup(he->line);
	if (!full)
		return (line);
	free(line);
	return (full);
}

int	has_trailing_pipe(const char *line)
{
	char	q;
	int		last;
	int		i;

	q = 0;
	last = -1;
	i = 0;
	while (line[i])
	{
		if (!q && (line[i] == '\'' || line[i] == '"'))
			q = line[i];
		else if (q && line[i] == q)
			q = 0;
		else if (!q && line[i] == '|')
			last = i;
		i++;
	}
	if (last < 0)
		return (0);
	i = last + 1;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	return (line[i] == '\0');
}
