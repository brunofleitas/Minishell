/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:16:27 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 12:18:19 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del)
		return ;
	if (lst)
	{
		del(lst->content);
		free(lst);
	}
	lst = NULL;
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

// Assuming the existence of a 'del' function to free the content.
void	del(void *content);

// Prototype of a function to create a new list element.
t_list	*ft_lstnew(void *content);

int	main(void)
{
	t_list	*element;

	// Create a new list element with content
	element = ft_lstnew(strdup("Element content")); // Using strdup for demo
	// Assuming print_element exists to verify the content before deletion
	print_element(element);
	// Delete and free the single element
	ft_lstdelone(element, &del);
	// After deletion, the element pointer should not be used as it's freed.
	printf("Element has been deleted and freed.\n");
	return (0);
}

void	del(void *content)
{
	free(content); // Free the dynamically allocated string or content
}

void	print_element(t_list *lst)
{
	if (lst && lst->content)
	{
		printf("Element content: %s\n", (char*)lst->content);
	}
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_lstdelone` takes a single list element and a function to delete its content.
It applies the function to the element's content to properly free it, then frees
the element itself. This is used to cleanly remove an element from a list
without leaving memory leaks.
*/
