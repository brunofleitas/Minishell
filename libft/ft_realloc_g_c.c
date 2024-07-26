#include "libft.h"

void    *ft_realloc_g_c(t_ntc **first_node, void *existing_data, size_t new_size)
{
    t_ntc   *new_node;
    size_t  old_size;
    void    *new_data;

    if (existing_data == NULL)
    {
        new_node = g_c(first_node, new_size);
        if (!new_node)
            return (NULL);
        new_data = new_node->data;
    }
    else
    {
        new_node = g_c(first_node, new_size);
        if (!new_node)
            return (NULL);
        new_data = new_node->data;
        old_size = find_ntc(first_node, existing_data)->size; 
        if (new_size < old_size)
            ft_memcpy(new_data, existing_data, new_size);
        else
            ft_memcpy(new_data, existing_data, old_size);
        free_ntc_prior(first_node, existing_data);
    }
    return (new_data);
}