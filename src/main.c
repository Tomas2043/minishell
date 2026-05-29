/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/05/26 11:56:46 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static t_token	*tokenize_input(char *line)
{
	char	**split;
	t_token	*tokens;

	split = ms_tokenize(line);
	if (!split)
		return (NULL);
	tokens = build_token_list(split);
	free_split(split);
	return (tokens);
}

void	handle_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	size_t	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return ;
	tokens = tokenize_input(line);
	if (!tokens)
		return (ft_putendl_fd("minishell: syntax error: unclosed quote", 2),
			(void)(shell->exit_status = 2));
	if (!check_syntax(tokens))
		return (ft_putendl_fd("minishell: syntax error near unexpected token",
				2), shell->exit_status = 2, free_tokens(tokens));
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmds)
		return ;
	expand_all(cmds, shell);
	execute(cmds, shell);
	free_cmd_list(cmds);
}

static void	shell_run_loop(t_shell *shell)
{
	char	*line;

	rl_done = 0;
	using_history();
	line = readline("minishell$ ");
	if (g_signal == SIGINT)
	{
		shell->exit_status = 130;
		g_signal = 0;
	}
	if (!line)
	{
		write(1, "exit\n", 5);
		rl_clear_history();
		shell->running = 0;
		return ;
	}
	if (*line)
		process_input_line(line, shell);
	else
		free(line);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = init_env(envp);
	shell.exit_status = 0;
	shell.running = 1;
	shell.hd_hist = NULL;
	shell.hd_input = NULL;
	shell.hd_cmd = NULL;
	shell.hd_hist_idx = 0;
	rl_catch_signals = 0;
	setup_signals();
	while (shell.running)
		shell_run_loop(&shell);
	free_list(shell.env);
	return (0);
}
