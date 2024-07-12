/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:27:13 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:28:36 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	k;

	k = 0;
	while (lst)
	{
		lst = lst->next;
		k++;
	}
	return (k);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Assuming the existence of ft_lstnew and ft_lstadd_back functions.

int	main(void)
{
	t_list	*head;
	int		size;

	head = NULL;
	// Add elements to the list
	ft_lstadd_back(&head, ft_lstnew("First element"));
	ft_lstadd_back(&head, ft_lstnew("Second element"));
	ft_lstadd_back(&head, ft_lstnew("Third element"));
	// Calculate the size of the list
	size = ft_lstsize(head);
	// Print the calculated size
	printf("The list contains %d elements.\n", size);
	// Free the list after use
	// Assuming a function like ft_lstclear is available for cleanup
	ft_lstclear(&head, &free);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstsize` counts how many elements are in a linked list. It goes through each
element, one by one, until it reaches the end of the list, keeping track of the
count along the way. This function helps you know the size of your list.
*/