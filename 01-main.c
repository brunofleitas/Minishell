/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01-main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:59:46 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 11:42:49 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "minishell.h"

char		*gnl(int fd);

/**
 * @brief Handles SIGINT (Ctrl+C) signal.
 *
 * This function is called when the SIGINT signal is received. It writes a
 * newline character to the standard output, resets the readline state, and
 * redisplays the prompt.
 *
 * @param sig Signal number (unused).
 */
void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/**
 * @brief Initializes the t_ma structure.
 *
 * Sets up the initial state of the t_ma structure:
 * - heredoc_f to 0
 * - first_node and first_env to NULL
 * - Joins and trims program name from argv[0]
 * - Calculates program name length
 * - last_exit_status to 0
 * - in_child_p to 0
 * - Duplicates environment variables
 * - Updates SHLVL to "SHLVL=3"
 *
 * @param ma Pointer to the t_ma structure.
 * @param argv Command-line arguments.
 * @param envp Environment variables.
 */
void	init_ma(t_ma *ma, char **argv, char **envp)
{
	ma->heredoc_f = 0;
	ma->first_node = NULL;
	ma->first_env = NULL;
	ma->program = ft_strjoin_g_c(argv[0], ": ", &(ma->first_node));
	ma->program = ft_strtrim_g_c(ma->program, "./", &(ma->first_node));
	ma->l_program = ft_strlen(ma->program);
	ma->last_exit_status = 0;
	ma->in_child_p = 0;
	ma->env = duplicate_vars(&(ma->first_env), envp);
	update_env_var(find_env_var(&(ma->env), "SHLVL"), "SHLVL=3", ma);
}

/**
 * @brief Processes the input for the shell.
 *
 * Handles input processing, including heredoc, history, lexing,
 * parsing, and executing the AST.
 *
 * @param ma Pointer to the main structure.
 * @param delimiters_h Pointer to the heredoc delimiters.
 * @param heredoc_f Pointer to the heredoc flag.
 */
void	process_input(t_ma *ma, char ***delimiters_h, int *heredoc_f)
{
	t_astnode	*root;

	if (!isatty(0) && *heredoc_f)
	{
		close_heredoc(delimiters_h, heredoc_f, ma);
		return ;
	}
	if (ma->input == NULL)
		builtin_exit(ma, NULL);
	if (ft_strcmp(ma->input, "") != 0)
	{
		if (isatty(0))
			add_history(ma->input);
		lexer(ma);
		if (!isatty(0))
			heredoc_checker(delimiters_h, heredoc_f, ma);
		if (ma->tkns[0] != NULL)
		{
			ma->and_or = 0;
			root = parser(ma);
			execute_ast(root, ma);
		}
		free_memory(&(ma->first_node));
	}
}

/**
 * @brief Restores saved file descriptors for stdin, stdout, and stderr.
 *
 * @param ma Pointer to the t_ma structure.
 * @param fix_stdin Pointer to saved stdin fd.
 * @param fix_stdout Pointer to saved stdout fd.
 * @param fix_stderr Pointer to saved stderr fd.
 */
void	restore_io_fds(t_ma *ma, int *fix_stdin, int *fix_stdout,
		int *fix_stderr)
{
	ma->saved_stdin = *fix_stdin;
	ma->saved_stdout = *fix_stdout;
	ma->saved_stderr = *fix_stderr;
}

/**
 * @file 01-main.c
 * @brief Entry point for the Minishell program.
 *
 * Initializes the Minishell environment and processes user input in a loop.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @param envp Array of environment variables.
 *
 * @return Always returns 0.
 */
int	main(int argc, char **argv, char **envp)
{
	t_ma	ma;
	int		fix [3];
	char	**delimiters_h;

	delimiters_h = NULL;
	(void)argc;
	fix[0] = dup(STDIN_FILENO);
	fix[1] = dup(STDOUT_FILENO);
	fix[2] = dup(STDERR_FILENO);
	init_ma(&ma, argv, envp);
	while (1)
	{
		restore_io_fds(&ma, &fix[0], &fix[1], &fix[2]);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		if (!isatty(0))
			ma.input = gnl(0);
		else
			ma.input = readline("\033[1;32mminishell>>\033[0m");
		process_input(&ma, &delimiters_h, &(ma.heredoc_f));
		restore_io(&ma);
		free(ma.input);
	}
	return (0);
}

/* Here's a command to run Valgrind with detailed options for your program 
(replace ./your_program with the actual path to your executable):

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes 
./your_program  */
// void	free_gnl_buffer(void) __attribute__((destructor));

// void	free_gnl_buffer(void)
// {
// 	gnl(-1);
// }
