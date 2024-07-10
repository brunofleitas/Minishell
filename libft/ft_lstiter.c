/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:19:14 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:22:00 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!f)
		return ;
	if (lst)
	{
		while (lst->next != NULL)
		{
			f(lst->content);
			lst = lst->next;
		}
		f(lst->content);
	}
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Assuming the existence of a function to apply to each element's content.
void	apply_function(void *content);

// Prototype for creating a new list element (assuming it exists).
t_list	*ft_lstnew(void *content);

// Function to print the list's content for verification.
void	print_list(t_list *lst);

int	main(void)
{
	t_list	*head;
	t_list	*newElement;

	head = NULL;
	// Create and add elements to the list
	newElement = ft_lstnew("First element");
	ft_lstadd_back(&head, newElement);
	newElement = ft_lstnew("Second element");
	ft_lstadd_back(&head, newElement);
	newElement = ft_lstnew("Third element");
	ft_lstadd_back(&head, newElement);
	// Print the list before applying the function
	printf("Before applying function:\n");
	print_list(head);
	// Apply a function to each element's content
	ft_lstiter(head, &apply_function);
	// Print the list after applying the function
	printf("\nAfter applying function:\n");
	print_list(head);
	// Free the list after use
	// Assuming ft_lstclear or equivalent function for cleanup
	ft_lstclear(&head, &free);
	return (0);
}

void	apply_function(void *content)
{
	// Example function that just prints the content
	printf("Function applied to: %s\n", (char *)content);
}

void	print_list(t_list *lst)
{
	while (lst != NULL)
	{
		printf("%s -> ", (char*)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstiter` goes through each element of a list and applies a given function
to the content of each element. It's useful for performing operations on all
items in a list, like modifying them or printing their values, without manually
iterating over the list.
*/