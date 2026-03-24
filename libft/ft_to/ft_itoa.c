/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toandrad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 13:41:36 by toandrad          #+#    #+#             */
/*   Updated: 2025/04/21 14:50:31 by toandrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int		len;
	long	num;

	len = 1;
	num = n;
	if (num < 0)
	{
		len++;
		num *= -1;
	}
	while (num >= 10)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	num;

	len = ft_numlen(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	num = n;
	if (num < 0)
	{
		str[0] = '-';
		num *= -1;
	}
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		len--;
		str[len] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}
