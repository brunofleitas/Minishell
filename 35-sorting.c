#include "minishell.h"

static int minishell_strcmp(const char *s1, const char *s2) 
{
	char    c1;
	char    c2;

    while (*s1 && *s2) 
    {
        c1 = *s1;
        c2 = *s2;
        if (c1 >= 'A' && c1 <= 'Z') 
        	c1 += 32;
        if (c2 >= 'A' && c2 <= 'Z') 
        	c2 += 32;
        if (c1 != c2)
            return c1 - c2;
        char *cpy_s1 = (char *)s1;
        char *cpy_s2 = (char *)s2;
        cpy_s1++;
        cpy_s2++;
        if (!*cpy_s1 && *cpy_s2)
            return -1;
        if (*cpy_s1 && !*cpy_s2)
            return 1;
        // If lowercase versions are the same, but original chars different,
        // lowercase comes first
        if (*s1 != *s2)
        {
            //return (*s2 & 32) - (*s1 & 32);
            if (*s1 > *s2) 
                return (-1);
            else 
                return (1);
        }
        s1++;
        s2++;
    }
    //return *s1 - *s2;
    if (*s1)
        return (1);
    else if (*s2)
        return (-1);
    else 
        return (0);
}

/**
 * Swaps two string pointers.
 *
 * @param a Pointer to the first string pointer
 * @param b Pointer to the second string pointer
 */
static void swap_strings(char **a, char **b) 
{
    char    *temp;
    
    temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Sorts an array of strings using bubble sort algorithm.
 *
 * @param arr Array of string pointers to be sorted
 * @param n Number of strings in the array
 */
void minishell_sort_str(char *arr[], int n) 
{
    int i;
    
    i = 0;
    while (i < n - 1) 
    {
        int j = 0;
        while (j < n - i - 1) 
        {
            if (minishell_strcmp(arr[j], arr[j + 1]) > 0) 
            {
                swap_strings(&arr[j], &arr[j + 1]);
            }
            j++;
        }
        i++;
    }
}

/**
 * Sorts an array of strings using bubble sort algorithm.
 *
 * @param arr Array of string pointers to be sorted
 * @param n Number of strings in the array
 */