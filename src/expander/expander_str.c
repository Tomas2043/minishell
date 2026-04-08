/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:50:37 by darafael          #+#    #+#             */
/*   Updated: 2026/04/07 18:14:47 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*get_var(char *str, int *skip)
{
	int		len;
	char	*name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	name = ft_substr(str, 0, len);
	*skip = len;
	return (name);
}

static char	*append_char(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = ft_strjoin(result, buf);
	free(result);
	return (tmp);
}

static char	*handle_dollar(char *str, char *result, int *i, t_shell *shell)
{
	char	*expanded;
	char	*tmp;

	expanded = expand_var(str, i, shell);
	tmp = ft_strjoin(result, expanded);
	free(result);
	free(expanded);
	return (tmp);
}

char	*expand_string(char *str, t_shell *shell)
{
	char	*result;
	int		i;
	int		sq;

	result = ft_strdup("");
	i = 0;
	sq = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !sq)
		{
			sq = 1;
			i++;
		}
		else if (str[i] == '\'' && sq)
		{
			sq = 0;
			i++;
		}
		else if (str[i] == '$' && !sq && str[i + 1])
			result = handle_dollar(str, result, &i, shell);
		else
			result = append_char(result, str[i++]);
	}
	return (result);
}
