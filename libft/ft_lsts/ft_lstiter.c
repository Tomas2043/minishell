/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darafael <darafael@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:45:33 by darafael          #+#    #+#             */
/*   Updated: 2025/04/30 08:13:58 by darafael         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*temp;

	if (lst == NULL || f == NULL)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->next;
	}
}
/*#include <stdio.h>

void	f(void *content)
{
	printf("%s\n", (char *)content);
}

//	void	f(void *content)
//	{
//	char **ptr = (char **)&content;
//	free(*ptr);
//	*ptr = strdup("Funciona");
//	}

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
	ft_lstiter(node2, f);
//	printf("%s\n", (char *)node3->content);
	return (0);
}*/