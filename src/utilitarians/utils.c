/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:34:14 by darafael          #+#    #+#             */
/*   Updated: 2026/04/06 13:33:57 by toandrad         ###   ########.fr       */
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
