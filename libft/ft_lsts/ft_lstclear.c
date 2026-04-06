/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:34:37 by darafael          #+#    #+#             */
/*   Updated: 2025/04/30 07:46:26 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*rem;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (*lst)
	{
		rem = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = rem;
	}
	*lst = NULL;
}
/*#include <stdio.h>

void	del(void *content)
{
	free(content);
}

int	main(void)
{
	t_list *list = NULL;
	t_list *node1 = ft_lstnew(strdup("First"));
	t_list *node2 = ft_lstnew(strdup("Second"));
	t_list *node3 = ft_lstnew(strdup("Third"));
	t_list *node4 = ft_lstnew(strdup("Fourth"));
	ft_lstadd_back(&list, node1);
	ft_lstadd_back(&list, node2);
	ft_lstadd_back(&list, node3);
	ft_lstadd_back(&list, node4);
	ft_lstclear(&node3, del);
	printf("%s\n", (char *)node4->content);
	return (0);
}*/