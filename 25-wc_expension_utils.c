#include "minishell.h"

static int	process_directory(t_wc_args *a, DIR *dir, char *pattern, t_ma *ma);

/**
 * @brief Expand wildcard patterns in a single argument
 *
 * This function expands wildcard patterns in a single argument.
 *
 * @param a Pointer to the wildcard argument structure
 * @param arg The argument to expand
 * @param ma Pointer to the memory allocation structure
 * @return int Returns 1 on success, 0 on error
 */
int	expand_wildcard(t_wc_args *a, char *pattern, t_ma *ma)
{
	DIR				*dir;
	char			*current_dir;
	// printf("pattern: %s\n", pattern);
	// printf("expand_wildcard_start\n");
	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return (0);
	dir = opendir(current_dir);
	if (!dir)
	{
		free(current_dir);
		return (0);
	}
	if(!process_directory(a, dir, pattern, ma))
	{
		closedir(dir);
		free(current_dir);
		return (0);
	}
	closedir(dir);
	free(current_dir);
	// printf("expand_wildcard_end\n");
	return (1);
}

/**
 * @brief Process a directory for wildcard expansion
 *
 * This function processes a directory for wildcard expansion. It reads the
 * directory entries and adds matching entries to the expended_single_arg array.
 *
 * @param a Pointer to the wildcard argument structure
 * @param dir Pointer to the directory stream
 * @param pattern The wildcard pattern to match against
 * @param ma Pointer to the memory allocation structure
 * @return int Returns 1 on success, 0 on error
 */
static int	process_directory(t_wc_args *a, DIR *dir, char *pattern, t_ma *ma)
{
	struct dirent	*entry;

	// printf("process_directory_start\n");
	entry = readdir(dir);
	while (entry != NULL)
	{
		// printf("entry->d_name: %s\n", entry->d_name);
		if (match_pattern(entry->d_name, pattern))
		{
			
			if (!add_single_element(a, entry->d_name, ma))
				return (0);
		}
		entry = readdir(dir);
	}
	// printf("process_directory_end\n");
	return (1);
}
/* readdir = Read a directory entry from DIRP.  Return a pointer to a `struct
   dirent' describing the entry, or NULL for EOF or error.  The
   storage returned may be overwritten by a later readdir call on the
   same DIR stream.

   If the Large File Support API is selected we have to use the
   appropriate interface.

   This function is a possible cancellation point and therefore not
   marked with __THROW.  
*/


/**
 * @brief Add a single element to the expanded argument array
 *
 * This function adds a single element to the expanded argument array.
 *
 * @param a Pointer to the wildcard argument structure
 * @param name The element to add
 * @param ma Pointer to the memory allocation structure
 * @return int Returns 1 on success, 0 on error
 */
int add_single_element(t_wc_args *a, char *name, t_ma *ma)
{
    int i;

    i = a->count - 1;
    if(a->count == a->capacity || a->count == a->capacity - 1)
    {
        a->exp_args = ft_realloc_g_c(&(ma->first_node), a->exp_args, sizeof(char *) * (a->count + 10));
        a->capacity = a->capacity + 10;
    }
    if (!a->exp_args)
        return (0);
    (a->exp_args)[a->count] = ft_strdup_g_c(name, &(ma->first_node));
    if (!(a->exp_args)[a->count])
    {
        while (i--)
            free_ntc_prior(&(ma->first_node), (a->exp_args) + i);
        return (0);
    }
    (a->count)++;
    return (1);
}
