/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/04/06 11:36:22 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	main(void)
{
	char	*line;

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
	return (0);
}
