/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 10:13:54 by darafael          #+#    #+#             */
/*   Updated: 2025/04/30 08:12:38 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	last = ft_lstlast(*lst);
	if (last == NULL)
	{
		*lst = new;
		return ;
	}
	last->next = new;
}
/*#include <stdio.h>

int	main(void)
{
	t_list *list = NULL;
	t_list *node1 = ft_lstnew("First");
	t_list *node2 = ft_lstnew("Second");
	t_list *node3 = ft_lstnew("Third");
	t_list *node4 = ft_lstnew("Fourth");
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	ft_lstadd_back(&list, node4);
	while (list)
	{
		printf("%s\n", (char *)list->content);
		list = list->next;
	}
	t_list *last = list;
	t_list *next;
	while (last)
	{
			next = last->next;
			last = next;
	}
	return (0);
}*/