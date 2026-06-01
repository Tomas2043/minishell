/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:03:44 by darafael          #+#    #+#             */
/*   Updated: 2026/06/01 11:01:11 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*expand_var(char *str, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*expanded;
	int		skip;

	if (str[*i + 1] == '?')
		return ((*i) += 2, ft_itoa(shell->exit_status));
	var_name = get_var(&str[*i + 1], &skip);
	if (!var_name)
		return (NULL);
	if (skip == 0)
	{
		free(var_name);
		(*i)++;
		return (ft_strdup("$"));
	}
	var_value = get_env(shell->env, var_name);
	free(var_name);
	if (var_value)
		expanded = ft_strdup(var_value);
	else
		expanded = ft_strdup("");
	*i += skip + 1;
	return (expanded);
}

static int	expand_args_strings(char **argv, int *keep, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	while (argv[i])
	{
		keep[i] = is_quoted_empty(argv[i]);
		expanded = expand_string(argv[i], shell);
		free(argv[i]);
		if (!expanded)
			return (0);
		argv[i] = expanded;
		i++;
	}
	return (1);
}

static void	expand_argv(t_cmd *cmd, t_shell *shell)
{
	int	*keep;
	int	argc;

	argc = 0;
	while (cmd->argv[argc])
		argc++;
	keep = ft_calloc(argc, sizeof(int));
	if (!keep)
		return ;
	if (!expand_args_strings(cmd->argv, keep, shell))
		return (free(keep));
	compact_empty_args(cmd->argv, keep);
	free(keep);
}

static void	expand_redirs(t_redir *redirs, t_shell *shell)
{
	t_redir	*current;
	char	*expanded;

	current = redirs;
	while (current)
	{
		if (current->type != REDIR_HEREDOC)
		{
			expanded = expand_string(current->filename, shell);
			if (!expanded)
				return ;
			free(current->filename);
			current->filename = expanded;
		}
		current = current->next;
	}
}

void	expand_all(t_cmd *cmds, t_shell *shell)
{
	t_cmd	*current;

	current = cmds;
	while (current)
	{
		expand_argv(current, shell);
		expand_redirs(current->redirs, shell);
		current = current->next;
	}
}
