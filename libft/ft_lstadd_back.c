/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:03:22 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:05:07 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tempo;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tempo = *lst;
	while (tempo->next != NULL)
		tempo = tempo->next;
	tempo->next = new;
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

void	print_list(t_list *lst);

int	main(void)
{
	t_list	*head;
	t_list	*newElement;

	head = NULL;
	// Create and add the first element
	newElement = ft_lstnew("First");
	ft_lstadd_back(&head, newElement);
	// Create and add the second element
	newElement = ft_lstnew("Second");
	ft_lstadd_back(&head, newElement);
	// Create and add the third element
	newElement = ft_lstnew("Third");
	ft_lstadd_back(&head, newElement);
	// Print the list to verify
	print_list(head);
	// Free the list after use
	// Assuming you have a function to properly free the list elements
	ft_lstclear(&head, &free);
	return (0);
}

void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstadd_back` adds a new element to the end of a list. If the list is empty,
it sets the new element as the start. This ensures the new element is always
the last one, maintaining the list's order.
*/