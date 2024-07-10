/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:00:12 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:00:55 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tempo;

	tempo = *lst;
	*lst = new;
	new->next = tempo;
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Assuming the existence of ft_lstnew and a print_list function.

void	print_list(t_list *lst);

int	main(void)
{
	t_list	*head;
	t_list	*newElement;

	head = NULL;
	// Create and add the first element to the front
	newElement = ft_lstnew("First");
	ft_lstadd_front(&head, newElement);
	// Create and add the second element to the front
	newElement = ft_lstnew("Second");
	ft_lstadd_front(&head, newElement);
	// Create and add the third element to the front
	newElement = ft_lstnew("Third");
	ft_lstadd_front(&head, newElement);
	// Print the list to verify the order
	print_list(head);
	// Free the list after use (assuming ft_lstclear is available)
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
`ft_lstadd_front` puts a new element at the start of a list. If you have a chain
of elements, this function adds the new one before all others, making it the
first in line. This is useful for quickly inserting items without going through
the entire list.
*/