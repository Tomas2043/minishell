/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/27 11:55:44 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
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

static void	handle_line(char *line, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize_input(line);
	if (!tokens)
		return ;
	if (!check_syntax(tokens))
	{
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
		shell->exit_status = 2;
		free_tokens(tokens);
		return ;
	}
	cmds = parse_tokens(tokens);
	free_tokens(tokens);
	if (!cmds)
		return ;
	expand_all(cmds, shell);
	execute(cmds, shell);
	free_cmd_list(cmds);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	shell;

	(void)ac;
	(void)av;
	shell.env = init_env(envp);
	shell.exit_status = 0;
	shell.running = 1;
	setup_signals();
	while (shell.running)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			if (g_signal == SIGINT)
			{
				shell.exit_status = 130;
				g_signal = 0;
				continue ;
			}
			write(1, "exit\n", 5);
			rl_clear_history();
			break ;
		}
		g_signal = 0;
		if (*line)
		{
			add_history(line);
			handle_line(line, &shell);
		}
		free(line);
	}
	free_list(shell.env);
	return (0);
}
