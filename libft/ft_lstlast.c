/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:23:16 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:24:45 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tempo;

	if (!lst)
		return (NULL);
	tempo = lst;
	while (tempo->next != NULL)
		tempo = tempo->next;
	return (tempo);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Assuming the existence of ft_lstnew and a function to add elements to the
list.
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

int	main(void)
{
	t_list	*head;
	t_list	*last;

	head = NULL;
	// Create and add elements to the list
	ft_lstadd_back(&head, ft_lstnew("First element"));
	ft_lstadd_back(&head, ft_lstnew("Second element"));
	ft_lstadd_back(&head, ft_lstnew("Third element"));
	// Use ft_lstlast to find the last element
	last = ft_lstlast(head);
	// Print the content of the last element
	if (last != NULL)
		printf("Last element content: %s\n", (char*)last->content);
	else
		printf("The list is empty.\n");
	// Free the list after use
	// Assuming ft_lstclear or equivalent function for cleanup
	ft_lstclear(&head, &free);
	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstlast` finds the last element in a list. If you have a chain of elements,
it walks through each one until it reaches the end. Then, it returns this final
element. If the list is empty, it returns NULL, indicating there's no last
element to find.
*/