/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_building.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 11:19:04 by darafael          #+#    #+#             */
/*   Updated: 2026/03/30 12:51:29 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	get_token_type(char *s)
{
	if (!ft_strcmp(s, "|"))
		return (TOK_PIPE);
	if (!ft_strcmp(s, "<"))
		return (TOK_REDIR_IN);
	if (!ft_strcmp(s, ">"))
		return (TOK_REDIR_OUT);
	if (!ft_strcmp(s, "<<"))
		return (TOK_HEREDOC);
	if (!ft_strcmp(s, ">>"))
		return (TOK_APPEND);
	return (TOK_WORD);
}

static t_token	*new_token(t_token_type type, char *value)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free(node);
		return (NULL);
	}
	node->next = NULL;
	return (node);
}

static void	add_token_back(t_token **lst, t_token *new_node)
{
	t_token	*tmp;

	if (!lst || !new_node)
		return ;
	if (!*lst)
	{
		*lst = new_node;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

static int	fill_token_list(t_token **tokens, char **split, size_t i)
{
	t_token	*new_node;
	t_token	*tmp;

	while (split[i])
	{
		new_node = new_token(get_token_type(split[i]), split[i]);
		if (!new_node)
		{
			while (*tokens)
			{
				tmp = (*tokens)->next;
				free((*tokens)->value);
				free(*tokens);
				*tokens = tmp;
			}
			return (0);
		}
		add_token_back(tokens, new_node);
		i++;
	}
	return (1);
}

t_token	*build_token_list(char **split)
{
	t_token	*tokens;

	if (!split)
		return (NULL);
	tokens = NULL;
	if (!fill_token_list(&tokens, split, 0))
		return (NULL);
	return (tokens);
}
