/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/06/01 13:34:34 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*read_continued_line(char *line, t_shell *shell)
{
	char	*cont;

	if (!isatty(STDIN_FILENO))
		return (line);
	setup_cont_signals();
	rl_event_hook = cont_event_hook;
	while (find_unclosed_quote(line) || has_trailing_pipe(line))
	{
		cont = readline("> ");
		if (!cont || g_signal == SIGINT)
			return (cancel_cont(line, cont, shell));
		line = append_cont_line(line, cont);
	}
	restore_signals();
	return (line);
}

static t_token	*tokenize_and_check(char *line, t_shell *shell)
{
	t_token	*tokens;
	char	**split;
	char	*bad;

	split = ms_tokenize(line);
	if (!split)
		return (NULL);
	tokens = build_token_list(split);
	free_split(split);
	if (!check_syntax(tokens, &bad))
	{
		print_syntax_error(bad);
		shell->exit_status = 2;
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

void	handle_line(char **linep, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;
	char	*line;
	size_t	i;

	i = 0;
	line = *linep;
	while (line[i] && is_space(line[i]))
		i++;
	if (!line[i])
		return ;
	line = read_continued_line(line, shell);
	*linep = line;
	if (!line)
		return ((void)(shell->exit_status = 130));
	tokens = tokenize_and_check(line, shell);
	if (!tokens)
		return ;
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
