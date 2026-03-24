/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 14:03:33 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/06 11:27:12 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	size_t	j;

	if (*to_find == '\0')
		return ((char *)str);
	i = 0;
	while (i < len && str[i])
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (i + j < len && to_find[j] && str[i + j] == to_find[j])
				j++;
			if (to_find[j] == '\0')
				return ((char *)(str + i));
		}
		i++;
	}
	return (NULL);
}
