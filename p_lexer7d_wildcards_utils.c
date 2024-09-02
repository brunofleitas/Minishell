#include "minishell.h"

/**
 * @brief Add a single matching element to the wildcard expansion results.
 * 
 * This function adds a single matched file or directory to the wildcard arguments
 * structure. It allocates memory for the new match if necessary and updates the
 * count of matches.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param full_path The full path of the matched file or directory.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses ft_strdup_g_c to create a copy of the full path.
 * @note If memory allocation fails during the process, the function returns 0.
 */
int add_single_element(t_wcs_args *a, char *full_path, t_ma *ma)
{
    if (a->count_match >= a->max_matches)
    {
        int new_size = a->max_matches * 2 + 1;
        char **new_matches = ft_realloc_g_c(a->matches, sizeof(char *) * new_size, &(ma->first_node));
        if (!new_matches)
            return 0;
        a->matches = new_matches;
        a->max_matches = new_size;
    }

    a->matches[a->count_match] = ft_strdup_g_c(full_path, &(ma->first_node));
    if (!a->matches[a->count_match])
        return 0;

    a->count_match++;
    return 1;
}

/**
 * @brief Add a matching entry to the wildcard expansion results.
 * 
 * This function constructs the full path of a matching entry and adds it to
 * the wildcard expansion results using add_single_element.
 * 
 * @param a Pointer to the wildcard arguments structure.
 * @param dir_path The directory path of the entry.
 * @param entry_name The name of the entry.
 * @param ma Pointer to the memory allocation structure.
 * @return int Returns 1 on success, 0 on failure.
 * 
 * @note This function uses ft_strjoin_g_c to construct the full path.
 * @note If memory allocation fails during path joining, the function returns 0.
 */
int add_matching_entry(t_wcs_args *a, char *dir_path, char *entry_name, t_ma *ma)
{
    char *full_path;
    int result;

    full_path = ft_strjoin_g_c(dir_path, "/", &(ma->first_node));
    if (!full_path)
        return 0;
    
    full_path = ft_strjoin_g_c(full_path, entry_name, &(ma->first_node));
    if (!full_path)
        return 0;

    result = add_single_element(a, full_path, ma);
    
    // We don't need to free full_path as it's managed by the memory allocator

    return result;
}