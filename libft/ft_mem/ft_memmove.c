/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 14:42:53 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/06 11:22:51 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;

	if (len == 0 || dst == src)
		return (dst);
	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dest < source)
		return (ft_memcpy(dest, source, len));
	while (len--)
		dest[len] = source[len];
	return (dst);
}
