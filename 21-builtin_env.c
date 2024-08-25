/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21-builtin_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 00:51:32 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/25 08:43:39 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	calculate_total_env_length(t_env *env)
{
	size_t	total_length;
	int		i;

	total_length = 0;
	i = 0;
	while (env->var[i] != NULL)
	{
		total_length += ft_strlen(env->var[i]) + 1;
		i++;
	}
	return (total_length);
}

static char	*concatenate_env_vars(t_env *env, size_t total_length, t_ma *ma)
{
	char	*result;
	int		i;

	i = 0;
	result = (char *)ft_calloc_g_c((total_length + 1), sizeof(char),
			&(ma->first_node));
	if (!result)
		return (NULL);
	while (env->var[i] != NULL)
	{
		ft_strlcat(result, env->var[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	return (result);
}

int	builtin_env(char **args, t_ma *ma)
{
	size_t	total_length;
	char	*result;

	if (args[1] != NULL)
	{
		printf("env: too many arguments\n");
		return (EXIT_FAILURE);
	}
	total_length = calculate_total_env_length(ma->env);
	result = concatenate_env_vars(ma->env, total_length, ma);
	if (result)
	{
		printf("%s", result);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

/* int	builtin_env(char **args, t_ma *ma)
{
	int		i;
	size_t	total_length;
	char	*result;

	i = 0;
	total_length = 0;
	if (args[1] != NULL)
	{
		printf("env: too many arguments\n");
		return (EXIT_FAILURE);
	}
	while (ma->env->var[i] != NULL)
	{
		total_length += ft_strlen(ma->env->var[i]) + 1;
		i++;
	}
	result = (char *)ft_calloc_g_c((total_length + 1), sizeof(char),
			&(ma->first_node));
	if (!result)
		return (EXIT_FAILURE);

	i = 0;
	while (ma->env->var[i] != NULL)
	{
		ft_strlcat(result, ma->env->var[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	if (result)
	{
		printf("%s", result);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
} */

/* ==9291== Conditional jump or move depends on uninitialised value(s)
==9291==    at 0x10C3B7: ft_strlen (ft_strlen.c:20)
==9291==    by 0x10C481: ft_strlcat (ft_strlcat.c:22)
==9291==    by 0x10B87F: builtin_env (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10C2FE: execute_builtin (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10C043: execute_simple_cmd (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BA9D: execute_ast (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BD30: execute_pipeline (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BA7D: execute_ast (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x1095A3: main (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==  Uninitialised value was created by a heap allocation
==9291==    at 0x4848899: malloc (in
		/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==9291==    by 0x10CD00: util_g_c (P_g_c.c:102)
==9291==    by 0x10CD81: g_c (P_g_c.c:139)
==9291==    by 0x10B82A: builtin_env (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10C2FE: execute_builtin (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10C043: execute_simple_cmd (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BA9D: execute_ast (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BD30: execute_pipeline (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x10BA7D: execute_ast (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==    by 0x1095A3: main (in
		/home/pcasagra/42/minishell_brunos_branch/minishell)
==9291==
==9291== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)

The selected text from the terminal indicates a Valgrind memory error report. 
This report is showing that there is a conditional jump or move operation in 
your code that depends on uninitialized values. Specifically,
	the error is occurring in the ft_strlen function,
	which is being called by ft_strlcat. The uninitialized value was created
	 by a heap allocation in the util_g_c function,
	which is called by g_c, and then used in builtin_env.

To address this issue, you should:

Review the util_g_c and g_c functions: Ensure that any memory allocated with 
malloc (or similar functions) is properly initialized before being used. 
This can be done by setting the memory to zero with memset after allocation,
	or by ensuring that every path through the code initializes the memory 
	before it is used.

Check the implementation of ft_strlen and ft_strlcat: Since the uninitialized 
value is being used in these functions,
	make sure that they are correctly handling strings and are not reading 
	beyond the allocated memory or before the start of the string.

Use Valgrind with more detailed options: Running Valgrind with 
--leak-check=full --show-leak-kinds=all --track-origins=yes can provide 
more detailed information about where and how the uninitialized values 
are being created and used.

Debugging: Utilize debugging tools or manual debugging techniques to trace 
the execution of your program and understand how the uninitialized values 
are being propagated.

Here's a command to run Valgrind with detailed options for your program 
(replace ./your_program with the actual path to your executable):

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 
./your_program */