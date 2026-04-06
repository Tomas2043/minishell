/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:29:28 by darafael          #+#    #+#             */
/*   Updated: 2025/04/23 10:26:29 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}
/*#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;
	t_list *n1 = ft_lstnew("David");
	t_list *n2 = ft_lstnew("Rafael");
	t_list *n3 = ft_lstnew("Barreto");
	t_list *n4 = ft_lstnew("Dias");
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	list = n1;
	printf("%d\n", ft_lstsize(list));
	return (0);
}*/