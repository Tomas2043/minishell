/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/06 13:34:03 by toandrad         ###   ########.fr       */
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

static void	handle_line(char *line)
{
	char	**split;
	t_token	*tokens;

	split = ms_tokenize(line);
	if (!split)
		return ;
	tokens = build_token_list(split);
	free_split(split);
	if (!tokens)
		return ;
	if (!check_syntax(tokens))
		ft_putendl_fd("minishell: syntax error near unexpected token", 2);
	free_tokens(tokens);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_env	*env;
	t_env	*current;
	char	**array;
	int		i;

	(void)ac;
	(void)av;
	env = init_env(envp);
	current = NULL;
	array = NULL;
	i = 0;
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "exit\n", 5);
			rl_clear_history();
			break ;
		}
		if (*line)
		{
			add_history(line);
			handle_line(line);
		}
		free(line);
	}
	free_list(env);
	return (0);
}
