#include "minishell.h"

/**
 * Custom string comparison function.
 * Compares strings in a case-insensitive manner, with lowercase 
 * letters sorting before their uppercase counterparts.
 *
 * @param s1 Pointer to the first string
 * @param s2 Pointer to the second string
 * @return Negative if s1 < s2, positive if s1 > s2, zero if equal
 */
int minishell_strcmp(const char *s1, const char *s2) 
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
        // If lowercase versions are the same, but original chars different,
        // lowercase comes first
        if (*s1 != *s2)
            return (*s2 & 32) - (*s1 & 32);
        
        s1++;
        s2++;
    }
    
    return *s1 - *s2;
}

/**
 * Swaps two string pointers.
 *
 * @param a Pointer to the first string pointer
 * @param b Pointer to the second string pointer
 */
void swap_strings(char **a, char **b) 
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
void sort_strings(char *arr[], int n) 
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
minshell_sort_str(a->args[a->count_cpy], (a->count - a->count_cpy));