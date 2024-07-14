/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:43:16 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 16:43:18 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intrim(char const *s1, char const *set, int dir)
{
	int	i;

	i = 0;
	if (dir == -1)
		i = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i = i + dir;
	return (i);
}

static int	calclength(char const *s1, char const *set)
{
	size_t	ifirst;
	size_t	ilast;
	size_t	lnewstr1;

	lnewstr1 = ft_strlen(s1);
	ifirst = intrim(s1, set, 1);
	if ((ifirst) == lnewstr1)
		return (0);
	ilast = intrim(s1, set, -1);
	lnewstr1 = (ilast - ifirst) + 1;
	return (lnewstr1);
}

static void	populate(char *newstr, char const *s1, char const *set, int lnewstr)
{
	int	i;
	int	j;
	int	startpc;
	int	endpc;

	i = 0;
	j = 0;
	startpc = intrim(s1, set, 1);
	endpc = intrim(s1, set, -1);
	while (i < lnewstr && s1[j] != '\0')
	{
		if (j < startpc || j > endpc)
			j++;
		else
		{
			newstr[i] = s1[j];
			j++;
			i++;
		}
	}
	newstr[i] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set, t_ntc **first_node)
{
	int		lnewstr;
	char	*newstr;

	lnewstr = calclength(s1, set);
	newstr = g_c(first_node, (lnewstr + 1) * sizeof(char))->data;
	if (!newstr)
		return (NULL);
	populate(newstr, s1, set, lnewstr);
	return (newstr);
}
/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

int	main(void) {
	char const *s1 = "   Hello, World!   ";
	char const *set = " ";
	char *trimmed;

	// Test trimming spaces from both ends
	trimmed = ft_strtrim(s1, set);
	if (trimmed != NULL) {
		printf("Trimmed string: '%s'\n", trimmed);
		free(trimmed); // Remember to free the dynamically allocated memory
	} else {
		printf("Memory allocation failed.\n");
	}

	// Test with set containing multiple characters
	s1 = "***Hello, World!***";
	set = "*";
	trimmed = ft_strtrim(s1, set);
	if (trimmed != NULL) {
		printf("Trimmed string: '%s'\n", trimmed);
		free(trimmed);
	} else {
		printf("Memory allocation failed.\n");
	}

	// Test when characters in 'set' are not in 's1'
	s1 = "Hello, World!";
	set = "*";
	trimmed = ft_strtrim(s1, set);
	if (trimmed != NULL) {
		printf("Trimmed string: '%s'\n", trimmed);
		free(trimmed);
	} else {
		printf("Memory allocation failed.\n");
	}

	// Test with empty 'set'
	s1 = "   Hello, World!   ";
	set = "";
	trimmed = ft_strtrim(s1, set);
	if (trimmed != NULL) {
		printf("Trimmed string: '%s'\n", trimmed);
		free(trimmed);
	} else {
		printf("Memory allocation failed.\n");
	}

	return (0);
}
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_strtrim` removes specific characters from the beginning and end of a string.
You give it a string and a set of characters to trim away. It then creates a new
string, excluding these characters from both ends, and returns it. This is
useful for cleaning up strings by removing unwanted whitespace or other
characters without affecting the middle part of the string.
*/
