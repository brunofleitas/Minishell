/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 15:45:35 by pcasagra          #+#    #+#             */
/*   Updated: 2024/02/28 15:53:48 by pcasagra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	word_count(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_token(const char **s, char c, t_ntc **first_node)
{
	const char	*start;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	return (ft_substr_g_c(start, 0, *s - start, first_node));
}

char	**ft_split(char const *s, char c, t_ntc **first_node)
{
	int		i;
	int		words;
	char	**split;

	i = 0;
	words = word_count(s, c);
	split = (char **)(g_c(first_node, \
								sizeof(char *) * (words + 1))->data);
	if (!s || !split)
		return (NULL);
	while (i < words)
		split[i++] = get_next_token(&s, c, first_node);
	split[i] = NULL;
	return (split);
}

/* ************************************************************************** */
/*                                    TEST                                    */
/* ************************************************************************** */
/*
#include <stdio.h>

char		**ft_split(char const *s, char c);
		// Assuming ft_split is prototyped in "libft.h"

// Utility function to print the resulting array of strings
void	print_split_array(char **array) {
	if (!array) {
		printf("NULL array\n");
		return ;
	}
	for (int i = 0; array[i] != NULL; i++) {
		printf("'%s'\n", array[i]);
	}
}

int	main(void) {
	char **split_result;
	char const *s = "Hello world this is a test";
	char delimiter = ' ';

	// Splitting a normal sentence
	split_result = ft_split(s, delimiter);
	print_split_array(split_result);

	// Free the allocated memory
	for (int i = 0; split_result[i] != NULL; i++) {
		free(split_result[i]);
	}
	free(split_result);

	// Test with consecutive delimiters
	s = "Hello,,world,,this,,is,,a,,test";
	delimiter = ',';
	split_result = ft_split(s, delimiter);
	print_split_array(split_result);

	// Free the allocated memory
	for (int i = 0; split_result[i] != NULL; i++) {
		free(split_result[i]);
	}
	free(split_result);

	// Add more tests as needed for edge cases like empty strings,
		strings with only delimiters, etc.

	return (0);
}
*/
/* ************************************************************************** */
/*                         FUNCTION MECANIC EXPLAINED                         */
/* ************************************************************************** */
/*
word_count:
Counts words in s separated by c. It iterates through s, using in_word
flag to track when it enters or leaves a word. Increments count at each word
start. Returns total word count.

get_next_token:
Finds and allocates memory for the next word in s separated by c. Skips
leading delimiters, then marks the start of a word. Finds the word's end, and
uses ft_substr to allocate and copy the word, returning its pointer.

ft_split:
Splits s into an array of words using c as a delimiter. Uses word_count
to allocate memory for an array of pointers for each word plus a NULL terminator.
Iterates through s, using get_next_token to allocate and assign each word
to the array. Returns the array of word pointers.
*/
/* ************************************************************************** */
/*                          PURPOSE OF THE FUNCTION                           */
/* ************************************************************************** */
/*
`ft_split` slices a string into an array of strings, separated by a given
delimiter. Here's a clear explanation within the specified width:

1. **Input and Delimiter**: Takes a string (`s`) and a delimiter character (`c`)
 The goal is to split `s` into segments wherever `c` appears.

2. **Counting Words**: First, it counts how many segments or "words" will result
 after splitting `s` by `c`, to know how much memory to allocate for the array
 of string pointers.

3. **Allocating Array of Pointers**: Allocates memory for an array of pointers
to strings. This array will hold pointers to the start of each segment in `s`,
plus one extra pointer set to `NULL` to mark the end of the array.

4. **Allocating and Copying Segments**: For each segment identified between
delimiters `c`, it allocates a new string to hold a copy of that segment. Then,
it copies the segment from `s` into this new string.

5. **Assigning Pointers**: Each newly allocated string (segment) is assigned to
an element in the array of pointers. This process repeats until all segments
have been processed.

6. **End of Array**: The final pointer in the array is set to `NULL` to indicate
the end of the array, following C convention for arrays of pointers.

7. **Return Value**: Returns the array of string pointers, with each pointing to
 a segment of `s` split by `c`. If `s` is empty, or only contains delimiters, or
 memory allocation fails, appropriate actions are taken (e.g., returning `NULL`
 or an array with a single `NULL` pointer).

8. **Memory Management**: It’s the caller's responsibility to free the memory
allocated for the array and each string within it when they are no longer needed
*/