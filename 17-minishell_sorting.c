/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17-minishell_sorting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 03:54:37 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 04:08:24 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Compares two strings lexicographically, ignoring case sensitivity.
 *
 * This function compares two strings lexicographically, ignoring the case 
 * of alphabetic characters. It first compares the strings case-insensitively 
 * and, if the strings are identical in a case-insensitive comparison, it 
 * compares them case-sensitively. If both strings are identical except for 
 * case, it favors lowercase letters over uppercase.
 *
 * @param s1 The first string to compare.
 * @param s2 The second string to compare.
 * @return A negative value if s1 is less than s2, a positive value if s1 is 
 *         greater than s2, or 0 if the strings are equal.
 */
int	ft_strcmp2(char const *s1, char const *s2)
{
	size_t	i;
	int		diff;

	i = 0;
	while (s1[i] && s2[i] && ft_tolower(s1[i]) == ft_tolower(s2[i]))
		i++;
	diff = (unsigned char)ft_tolower(s1[i]) - (unsigned char)ft_tolower(s2[i]);
	if (diff)
		return (diff);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (ft_isalpha(s1[i]) && ft_isalpha(s2[i])
		&& ft_tolower(s1[i]) == ft_tolower(s2[i]))
	{
		return (s2[i] - s1[i]);
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/**
 * @brief Sorts an array of strings in lexicographical order.
 *
 * This function implements an insertion sort algorithm to sort an array of 
 * strings in lexicographical order. It compares adjacent strings and swaps 
 * them if they are out of order.
 *
 * @param tab The array of strings to sort.
 * @param size The number of elements in the array.
 */
void	minishell_sort_str(char *tab[], size_t size)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	i = 1;
	while (i < size)
	{
		j = i;
		while (j > 0)
		{
			if (ft_strcmp2(tab[j], tab[j - 1]) >= 0)
				break ;
			tmp = tab[j];
			tab[j] = tab[j - 1];
			tab[j - 1] = tmp;
			j--;
		}
		i++;
	}
}
