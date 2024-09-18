/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09-generate_double_operators.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:06:54 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 00:35:34 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Generates and stores double character operators.
 *
 * This function extracts double character operators from the input string 
 * (such as `&&` or `||`) and stores them in the split array. It also advances 
 * the input string pointer accordingly.
 *
 * @param s Pointer to the current position in the string being parsed.
 * @param split Array of strings where the double operators are stored.
 * @param i Pointer to the current index in the split array.
 * @param ma Pointer to the structure containing metadata for memory 
 *           allocation and state management.
 */
void	generate_double_operators(const char **s, char ***split, int *i,
		t_ma *ma)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, &(ma->first_node));
	*s += 2;
}
