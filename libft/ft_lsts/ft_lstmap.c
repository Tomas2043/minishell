/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:35:18 by darafael          #+#    #+#             */
/*   Updated: 2025/04/23 12:41:03 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newnode;
	t_list	*headlist;
	void	*newcontent;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	headlist = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		if (newcontent == NULL)
		{
			return (ft_lstclear(&headlist, del), NULL);
		}
		newnode = ft_lstnew(newcontent);
		if (newnode == NULL)
		{
			del(newcontent);
			return (ft_lstclear(&headlist, del), NULL);
		}
		ft_lstadd_back(&headlist, newnode);
		lst = lst->next;
	}
	return (headlist);
}
/*#include <stdio.h>

void	*duplicate_funciona(void *content)
{
	(void)content;
	return (strdup("Funciona"));
}

void	del(void *content)
{
	free(content);
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s\n", (char *)lst->content);
		lst = lst->next;
	}
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
	print_list(list);
	t_list *mapped = ft_lstmap(list, duplicate_funciona, del);
	print_list(mapped);
	ft_lstclear(&list, del);
	ft_lstclear(&mapped, del);
	return (0);
}*/