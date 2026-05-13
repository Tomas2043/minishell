

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

static char	**build_new_argv(t_cmd *cmd, int total, t_shell *shell)
{
	char	**new_argv;
	char	**wl;
	int		i;
	int		j;
	int		k;

	new_argv = malloc(sizeof(char *) * (total + 1));
	if (!new_argv)
		return (NULL);
	new_argv[total] = NULL;
	i = 0;
	k = 0;
	while (cmd->argv[i])
	{
		wl = expand_to_wordlist(cmd->argv[i++], shell);
		if (!wl)
			return (free(new_argv), NULL);
		j = 0;
		while (wl[j])
			new_argv[k++] = wl[j++];
		free(wl);
	}
	return (new_argv);
}

static void	expand_argv(t_cmd *cmd, t_shell *shell)
{
	char	**new_argv;
	char	**old;
	int		total;
	int		i;

	total = expand_argv_count(cmd, shell);
	if (total == -1)
		return ;
	new_argv = build_new_argv(cmd, total, shell);
	if (!new_argv)
		return ;
	old = cmd->argv;
	i = 0;
	while (old[i])
		free(old[i++]);
	free(old);
	cmd->argv = new_argv;
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
