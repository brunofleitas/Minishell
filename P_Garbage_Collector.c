/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Z_Garbage_Collector.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 10:32:29 by pcasagra          #+#    #+#             */
/*   Updated: 2024/04/18 10:32:30 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
The free_ntc_prior function is used to free a node in the garbage collector
list at any time during the execution of the program. It is usefull when we need
to free a node before the end of the program.
*/
void	free_ntc_prior(t_ntc **first_node, void *data_ptr)
{
	t_ntc	*temp;

	temp = *first_node;
	while (temp != NULL)
	{
		if (temp->data != NULL && temp->data == data_ptr)
			break ;
		temp = temp->next;
	}
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
	free(temp->data);
    temp->data = NULL;
    free(temp);
}

/*
The free_memory function is used to free all the nodes in the garbage
collector list. It is normally meant to be used at the end of the programm 
but could be used before if needed.
*/
void	free_memory(t_ntc **first_node)
{
	t_ntc	*temp;
	t_ntc	*next_node;

	temp = *first_node;
	while (temp != NULL)
	{
		next_node = temp->next;
		if (temp->data != NULL)
		{
			free(temp->data);
			temp->data = NULL;
		}
		free(temp);
		temp = next_node;
	}
	*first_node = NULL;
}

/*
The function util_garbage_collector is used to create a new node in the garbage
collector list.
*/
static t_ntc	**util_garbage_collector(t_ntc **new_node, size_t size_of)
{
	*new_node = malloc(sizeof(t_ntc));
	if (*new_node == NULL)
		return (NULL);
	(*new_node)->data = malloc(size_of);
	if ((*new_node)->data == NULL)
	{
		free(*new_node);
		return (NULL);
	}
	return (new_node);
}

/* The garbage_collector function is used to create a list of all the adresses
where we allocated memory on the heap. Each time we need to allocate space on
the heap for a new element regardless of its type we use this function. So each
time this function is called the adress of the new memory allocation on the
heap is stored in the list passed as first argument. This way, at the end of
the programm we can simply clean each element of the list one after the other
and there wont be any memory leaks.


Exemple of how to call  the function:

function() {
t_ntc	*first_node;

first_node = NULL;
garbage_collector(&first_node, sizeof(t_lst));
}

t_lst is the type of the data we want to store in the garbage collector list.
*/
t_ntc	*garbage_collector(t_ntc **first_node, size_t size_of)
{
	t_ntc	*temp;
	t_ntc	*new_node;

	if (!first_node)
		return (NULL);
	if (util_garbage_collector(&new_node, size_of) == NULL)
		return (NULL);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*first_node == NULL)
		*first_node = new_node;
	else
	{
		temp = *first_node;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new_node;
		temp->next->prev = temp;
	}
	return (new_node);
}

/*
ntc = node to clean
The first malloc allocates a new garbage collector node.
The second malloc allocates memory for the actual data (t_lst nodes)
*/