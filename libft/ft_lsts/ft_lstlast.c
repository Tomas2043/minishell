/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:42:31 by darafael          #+#    #+#             */
/*   Updated: 2025/04/30 08:15:22 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*last;

	if (lst == NULL)
		return (NULL);
	last = lst;
	while (last->next)
		last = last->next;
	return (last);
}
/*#include <stdio.h>

int	main(void)
{
	t_list *n1 = ft_lstnew("David");
	t_list *n2 = ft_lstnew("Rafael");
	t_list *n3 = ft_lstnew("Barreto");
	t_list *n4 = ft_lstnew("Dias");
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	t_list *last = ft_lstlast(n1);
	if (last)
		printf("%s\n", (char *)last->content);
	return (0);
}*/