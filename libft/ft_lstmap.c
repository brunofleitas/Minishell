/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 12:25:55 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 14:21:07 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped_l;
	t_list	*mapped_n;
	t_list	*last_mapped;

	mapped_l = NULL;
	last_mapped = NULL;
	while (lst)
	{
		mapped_n = malloc(sizeof(t_list));
		if (!mapped_n)
		{
			ft_lstclear(&mapped_l, del);
			return (NULL);
		}
		mapped_n->content = f(lst->content);
		mapped_n->next = NULL;
		if (!mapped_l)
			mapped_l = mapped_n;
		else
			last_mapped->next = mapped_n;
		last_mapped = mapped_n;
		lst = lst->next;
	}
	return (mapped_l);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

// Assuming the existence of necessary functions and t_list structure.

void	*duplicate_content(void *content);
void	del(void *content);
void	print_list(t_list *lst);

int	main(void)
{
	t_list	*list;
	t_list	*mapped_l;

	list = NULL;
	// Create and add elements to the original list
	ft_lstadd_back(&list, ft_lstnew(strdup("First")));
	ft_lstadd_back(&list, ft_lstnew(strdup("Second")));
	ft_lstadd_back(&list, ft_lstnew(strdup("Third")));
	// Map the list using ft_lstmap
	mapped_l = ft_lstmap(list, &duplicate_content, &del);
	// Print the mapped list to verify
	print_list(mapped_l);
	// Free both lists after use
	ft_lstclear(&list, &del);
	ft_lstclear(&mapped_l, &del);
	return (0);
}

void	*duplicate_content(void *content)
{
	// Example function that duplicates the string content
	return (strdup((char *)content));
}

void	del(void *content)
{
	// Example function that frees the string content
	free(content);
}

void	print_list(t_list *lst)
{
	while (lst)
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
`ft_lstmap` creates a new list by applying a given function to each element of
an existing list. It iterates over the original list, uses the function to
transform each element's content, and forms a new list with these transformed
elements. If memory allocation fails, it clears the new list and returns NULL.
*/