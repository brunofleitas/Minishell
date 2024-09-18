/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   29-AST_execute_pipeline.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:07:23 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/18 05:23:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes a child process in a pipeline.
 *
 * This function handles the child process created during pipeline execution. 
 * It sets up the input and output file descriptors for the command, handling 
 * pipes between processes. If redirections are present, they are processed. 
 * After setup, the child process executes the command.
 *
 * @param a Pointer to the structure containing pipeline arguments, 
 *          including file descriptors and process state.
 * @param simple_cmd Pointer to the simple command AST node to execute.
 * @param cmd_redir Pointer to the redirection AST node for the command, 
 *                  if any.
 * @param ma Pointer to the structure containing metadata for execution, 
 *           including child process state and memory management.
 */
void	child_process(t_pip_args *a, t_astnode *simple_cmd,
		t_astnode *cmd_redir, t_ma *ma)
{
	if (a->input_fd != STDIN_FILENO)
	{
		dup2(a->input_fd, STDIN_FILENO);
		close(a->input_fd);
	}
	if (!a->last_cmd)
	{
		dup2(a->pipe_fds[1], STDOUT_FILENO);
		close(a->pipe_fds[0]);
		close(a->pipe_fds[1]);
	}
	ma->in_child_p++;
	ma->and_or = 0;
	if (cmd_redir)
	{
		handle_redirections(cmd_redir, ma);
	}
	execute_ast(simple_cmd, ma);
}

/**
 * @brief Manages the parent process behavior in a pipeline.
 *
 * This function handles the parent process after forking a child process 
 * in a pipeline. It closes the input file descriptor if it's not `STDIN_FILENO`
 * and for all but the last command, it closes the write end of the pipe 
 * and prepares the read end for the next command in the pipeline.
 *
 * @param a Pointer to the structure containing pipeline arguments, 
 *          including file descriptors.
 */
void	parent_process(t_pip_args *a)
{
	if (a->input_fd != STDIN_FILENO)
		close(a->input_fd);
	if (!(a->last_cmd))
	{
		close(a->pipe_fds[1]);
		a->input_fd = a->pipe_fds[0];
	}
}

/**
 * @brief Creates a process for a command in the pipeline.
 *
 * This function forks a new process for a command in the pipeline. It sets 
 * up pipes for inter-process communication if the command is not the last 
 * one. The child process handles the command execution, with optional 
 * redirections, while the parent process manages the pipe and waits for 
 * the child to complete.
 *
 * @param a Pointer to the structure containing pipeline arguments, 
 *          including file descriptors and process IDs.
 * @param node Pointer to the pipeline AST node.
 * @param i The index of the current command in the pipeline.
 * @param ma Pointer to the structure containing metadata for execution, 
 *           including process and memory management.
 */
void	create_process(t_pip_args *a, t_astnode *node, int i, t_ma *ma)
{
	a->last_cmd = (i == node->data.pipeline.cmd_count - 1);
	if (!a->last_cmd)
	{
		if (pipe(a->pipe_fds) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	a->pid_arr[i] = fork();
	if (a->pid_arr[i] == -1)
		exit_or_setexit(1, 1, ma);
	if (a->pid_arr[i] == 0)
	{
		if (node->data.pipeline.cmds_redir)
			child_process(a, node->data.pipeline.cmds[i],
				node->data.pipeline.cmds_redir[i], ma);
		else
			child_process(a, node->data.pipeline.cmds[i], NULL, ma);
	}
	else
		parent_process(a);
}

/**
 * @brief Waits for all processes in a pipeline to finish.
 *
 * This function waits for each process in a pipeline to complete, capturing 
 * their exit statuses. Once all processes have finished, it sets the exit 
 * status based on the last process in the pipeline. If the last process 
 * exited normally, the exit status is set to its exit code. If it was 
 * terminated by a signal, the signal number is used as the exit status.
 *
 * @param cmd_count The number of commands (processes) in the pipeline.
 * @param pid_arr Array of process IDs for the commands in the pipeline.
 * @param ma Pointer to the structure containing metadata, including exit status 
 * 			 management.
 */
void	wait_for_all_processes(int cmd_count, pid_t *pid_arr, t_ma *ma)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid_arr[i], &status, 0);
		if (i == cmd_count - 1)
			last_status = status;
		i++;
	}
	if (WIFEXITED(last_status))
		exit_or_setexit(WEXITSTATUS(last_status), 0, ma);
	else if (WIFSIGNALED(last_status))
		exit_or_setexit(WTERMSIG(last_status), 0, ma);
}

/**
 * @brief Executes a pipeline of commands in a sequence.
 *
 * This function executes a pipeline of commands by creating child processes 
 * for each command in the pipeline. If the pipeline contains only a single 
 * built-in command, it executes it directly without forking. Otherwise, 
 * it forks processes, sets up the necessary pipes between commands, and waits 
 * for all processes to complete.
 *
 * @param node Pointer to the pipeline AST node.
 * @param ma Pointer to the structure containing metadata for execution, 
 *           including file descriptors and process management.
 */
void	execute_pipeline(t_astnode *node, t_ma *ma)
{
	t_pip_args	a;
	int			i;

	a.input_fd = STDIN_FILENO;
	if (node->data.pipeline.cmd_count == 1
		&& node->data.pipeline.cmds[0]->type == NODE_SIMPLE_CMD
		&& (node->data.pipeline.cmds[0]->data.simple_cmd.words
			&& node->data.pipeline.cmds[0]-> \
			data.simple_cmd.words[0].data.word.type == TOKEN_BUILTIN))
	{
		execute_ast(node->data.pipeline.cmds[0], ma);
		return ;
	}
	a.pid_arr = g_c(&(ma->first_node), sizeof(pid_t)
			* (node->data.pipeline.cmd_count))->data;
	i = 0;
	while (i < node->data.pipeline.cmd_count)
	{
		create_process(&a, node, i, ma);
		i++;
	}
	wait_for_all_processes(node->data.pipeline.cmd_count, a.pid_arr, ma);
}
