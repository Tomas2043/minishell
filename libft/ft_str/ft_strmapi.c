/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 14:25:43 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/07 12:48:54 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
/*static char	to_upper(unsigned int idx, char c)
{
	(void)idx;
	return (ft_toupper(c));
}

int	main(void)
{
	char	*s = "Hello, world!";
	char	*mapped;

	mapped = ft_strmapi(s, to_upper);
	if (!mapped)
		return (1);
	ft_putendl_fd(mapped, 1);
	free(mapped);
	return (0);
}*/
