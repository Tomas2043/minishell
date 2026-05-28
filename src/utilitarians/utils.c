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

void	build_and_add_history(char *line, t_shell *shell)
{
	char	*full;
	char	*with_nl;

	if (!shell->hd_hist)
	{
		add_history(line);
		return ;
	}
	full = ft_strjoin(line, shell->hd_hist);
	free(shell->hd_hist);
	shell->hd_hist = NULL;
	with_nl = ft_strjoin(full, "\n");
	free(full);
	if (with_nl)
		add_history(with_nl);
	free(with_nl);
}
