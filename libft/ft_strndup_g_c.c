#include "libft.h"

/**
 * @brief Duplicate up to n characters of a string and store it in a new memory location.
 * 
 * This function duplicates up to 'n' characters from the string 's' and stores 
 * them in a new memory location. It also updates the global variable 'g_c' 
 * with the newly allocated memory block. If 'n' is greater than the length of 's',
 * the entire string is duplicated.
 * 
 * @param s The string to be duplicated.
 * @param n The maximum number of characters to duplicate.
 * @param first_node A pointer to the first node of a linked list used for memory management.
 * @return char* A pointer to the newly allocated memory block containing the duplicated string.
 *         Returns NULL if memory allocation fails or if 's' is NULL.
 * 
 * @note The returned string is always null-terminated, even if 'n' characters
 *       were copied. This means the allocated memory is at most n+1 bytes.
 * @note If 's' is NULL, the function returns NULL without attempting to allocate memory.
 * @note The caller is responsible for freeing the memory allocated by this function
 *       when it's no longer needed, using the appropriate memory management function.
 */
char    *ft_strndup_g_c(const char *s, size_t n, t_ntc **first_node)
{
    size_t  len;
    char    *newstr;

    if (!s)
        return (NULL);

    len = ft_strlen(s);
    if (n < len)
        len = n;

    newstr = (char *)(g_c(first_node, len + 1)->data);
    if (newstr == NULL)
        return (NULL);

    ft_memcpy(newstr, s, len);
    newstr[len] = '\0';

    return (newstr);
}
