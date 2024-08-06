#include "libft.h"
#include <stdio.h>

void *ft_realloc_g_c(t_ntc **first_node, void *existing_data, size_t new_size)
{
    t_ntc   *new_node;
    t_ntc   *existing_node;
    size_t  old_size;
    void    *new_data;

    existing_node = NULL;
    if (existing_data == NULL)
    {
        new_node = g_c(first_node, new_size);
        if (!new_node)
        {
            printf("new_node is NULL existing data NULL\n");
            return (NULL);
        }
        new_data = new_node->data;
    }
    else
    {
        existing_node = find_ntc(first_node, existing_data);
        if (!existing_node)
        {
            printf("existing_node is NULL\n");
            return (NULL);
        }
        old_size = existing_node->size;
        new_node = g_c(first_node, new_size);
        if (!new_node)
        {
            printf("new_node is NULL\n");
            return (NULL);
        }
        new_data = new_node->data;
        if (new_size < old_size)
            ft_memcpy(new_data, existing_data, new_size);
        else
            ft_memcpy(new_data, existing_data, old_size);
        
        free_ntc_prior(first_node, existing_data);
    }
    return (new_data);
}