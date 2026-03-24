/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 12:07:42 by toandrad          #+#    #+#             */
/*   Updated: 2025/04/21 11:32:46 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isinset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static size_t	ft_getstart(const char *s1, const char *set)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		i++;
	return (i);
}

static size_t	ft_getend(const char *s1, const char *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i > 0 && ft_isinset(s1[i - 1], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = ft_getstart(s1, set);
	end = ft_getend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 1);
	return (str);
}
