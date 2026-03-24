/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:10:49 by toandrad          #+#    #+#             */
/*   Updated: 2025/04/17 11:27:05 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;
	size_t	strlen;
	size_t	substrlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	substrlen = strlen - start;
	if (substrlen > len)
		substrlen = len;
	substr = malloc(sizeof(char) * (substrlen + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < substrlen)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
