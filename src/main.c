/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 13:38:14 by toandrad          #+#    #+#             */
/*   Updated: 2026/03/30 12:57:34 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *token_type_name(t_token_type type)
{
	if (type == TOK_WORD)
		return("WORD");
	if (type == TOK_REDIR_IN)
		return("REDIRECT_IN");
	if (type == TOK_REDIR_OUT)
		return("REDIRECT_OUT");
	if (type == TOK_PIPE)
		return("PIPE");
	if (type == TOK_HEREDOC)
		return("HEREDOC");
	if (type == TOK_APPEND)
		return("APPEND");
	return ("UNKNOWN");	
}

static void	print_token_list(t_token *tokens)
{
	while (tokens)
	{
		printf("[%s] -> [%s]\n",
			token_type_name(tokens->type), tokens->value);
		tokens = tokens->next;
	}
}

static void	handle_line(char *line)
{
	char	**split;
	t_token	*tokens;
	t_token *tmp;

	split = ms_tokenize(line);
	if (!split)
	{
		printf("tokenizer error\n");
		return ;
	}
	tokens = build_token_list(split);
	free_split(split);
	if (!tokens)
	{
		printf("token list error\n");
		return ;
	}
	if (!check_syntax(tokens))
		printf("syntax error\n");
	else
		print_token_list(tokens);
	while (tokens)
	{
		tmp = (tokens)->next;
		free((tokens)->value);
		free(tokens);
		tokens = tmp;
	}
}

int	main(void)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
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