/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <toandrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:55:52 by toandrad          #+#    #+#             */
/*   Updated: 2025/05/07 12:15:28 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t	dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	copy_len;

	dst_len = 0;
	src_len = ft_strlen(src);
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	if (dst_len == dstsize)
		return (dstsize + src_len);
	copy_len = dstsize - dst_len - 1;
	if (copy_len > src_len)
		copy_len = src_len;
	ft_memcpy(dst + dst_len, src, copy_len);
	dst[dst_len + copy_len] = '\0';
	return (dst_len + src_len);
}
/*int	main(void)
{
	char dest[20] = "Hello ";
	const char *src = "World!";
	size_t result;

	printf("Before strlcat:\n");
	printf("dest: %s\n", dest);
	printf("src: %s\n", src);

	result = ft_strlcat(dest, src, sizeof(dest));

	printf("\nAfter strlcat:\n");
	printf("dest: %s\n", dest);
	printf("Return value: %zu\n", result);

	return (0);
}*/
