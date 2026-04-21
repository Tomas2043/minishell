/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 18:03:44 by darafael          #+#    #+#             */
/*   Updated: 2026/04/21 10:29:34 by toandrad         ###   ########.fr       */
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

void	expand_tokens(t_token *tokens, t_shell *shell)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TOK_WORD)
		{
			expanded = expand_string(current->value, shell);
			free(current->value);
			current->value = expanded;
		}
		current = current->next;
	}
}

static void	expand_argv(t_cmd *cmd, t_shell *shell)
{
	char	*expanded;
	int		i;

	i = 0;
	while (cmd->argv[i])
	{
		expanded = expand_string(cmd->argv[i], shell);
		free(cmd->argv[i]);
		cmd->argv[i] = expanded;
		i++;
	}
}

static void	expand_redirs(t_redir *redirs, t_shell *shell)
{
	t_redir	*current;
	char	*expanded;

	current = redirs;
	while (current)
	{
		expanded = expand_string(current->filename, shell);
		free(current->filename);
		current->filename = expanded;
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
