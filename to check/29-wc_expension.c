#include "minishell.h"

static int expand_single_arg(t_wc_args *a , char *arg, t_ma *ma);

/**
 * @brief Expand wildcard patterns in command arguments
 *
 * This function expands wildcard patterns in the command arguments. It
 * iterates through the arguments and calls expand_single_arg to handle
 * each argument. The function returns the expanded argument array.
 *
 * @param args The command arguments to expand
 * @param ma Pointer to the memory allocation structure
 * @return char** The expanded argument array, or NULL on error
 */
char    **expand_wildcards_in_args(char **args, t_ma *ma)
{
    t_wc_args   a;
    int     i;

    // printf("expand_wildcards_in_args_start\n");
    a.exp_args = NULL;
    a.count = 0;
    a.capacity = 0;
    i = 0;
    while (args[i])
    {
        if (!expand_single_arg(&a, args[i], ma))
            return (NULL);
        i++;
    }
    a.exp_args[a.count] = NULL;
    // printf("expand_wildcards_in_args_end\n");
    return (a.exp_args);
}

/**
 * @brief Expand wildcard patterns in a single argument
 *
 * This function expands wildcard patterns in a single argument. It checks
 * if the argument contains a wildcard character ('*') and calls expand_wildcard
 * to handle wildcard expansion. If the argument does not contain a wildcard,
 * it adds the argument to the expended_single_arg array.
 *
 * @param a Pointer to the wildcard argument structure
 * @param arg The argument to expand
 * @param ma Pointer to the memory allocation structure
 * @return int Returns 1 on success, 0 on error
 */
static int expand_single_arg(t_wc_args *a , char *arg, t_ma *ma)
{
    // printf("expand_single_arg_start\n");
    //printf("arg: %s\n", arg);
    if ((!(arg[0] == '\"' || arg[0] == '\'')) && (ft_strchr(arg, '*')) /* || ft_strchr(arg, '?') */)
    {
        if (!expand_wildcard(a, arg, ma))
            return (0);
    }
    else
    {
        if (!add_single_element(a, arg, ma))
        return (0);
    } 
    // printf("expand_single_arg_end\n");
    return (1);
}

