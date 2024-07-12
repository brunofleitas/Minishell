/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:08:14 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:14:47 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tempo;

	while (lst && *lst)
	{
		tempo = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tempo;
	}
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Prototype of the del function to properly free the content of a node.
void	del(void *content);

// Prototype of a function to create a new list element (assuming it exists).
t_list	*ft_lstnew(void *content);

int	main(void)
{
	t_list	*head;

	head = NULL;
	// Create and add elements to the list
	ft_lstadd_front(&head, ft_lstnew("First element"));
	ft_lstadd_front(&head, ft_lstnew("Second element"));
	ft_lstadd_front(&head, ft_lstnew("Third element"));
	// Assuming print_list exists to verify the list before clearing
	print_list(head);
	// Clear the list
	ft_lstclear(&head, &del);
	// The head should now be NULL. This condition checks that.
	if (head == NULL)
		printf("List has been cleared and is now NULL.\n");
	else
		printf("List clearing failed.\n");
	return (0);
}

void	del(void *content)
{
	free(content); // Free the malloc'ed string or whatever content you have
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
/*                         FUNCTION MECANIC EXPLAINED                         */
/* ************************************************************************** */
/*
while (lst && *lst)  // Check if list pointer or pointer to first node is NULL
{
	tempo = (*lst)->next;  // Save the next node
	ft_lstdelone(*lst, del);  // Delete the current node
	*lst = tempo;  // Move to the next node


*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstclear` goes through each element of a list, uses a given function to
delete and free the content of each element, and then frees the element itself.
Once done, it sets the list's start pointer to NULL, effectively clearing the
entire list. This ensures no memory leaks from the list elements or their
contents.
*/
