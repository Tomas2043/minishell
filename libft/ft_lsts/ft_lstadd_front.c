/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 17:06:03 by darafael          #+#    #+#             */
/*   Updated: 2025/04/30 07:43:57 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = *lst;
	*lst = new;
}
/*#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;
	t_list *node1 = ft_lstnew("First");
	t_list *node2 = ft_lstnew("Second");
	ft_lstadd_front(&list, node1);
	ft_lstadd_front(&list, node2);
	printf("%s\n", (char *)list->content);
	printf("%s\n", (char *)list->next->content);
	return (0);
}*/
