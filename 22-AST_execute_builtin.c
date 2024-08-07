#include "minishell.h"

static int	count_words(char **args)
{
	char	**temp;
	int		i;

	i = 0;
    temp = args;
	while (temp[i])
		i++;
	return (i);
}

/**
 * @brief Check if a command is a builtin
 *
 * This function checks if the given command is one of the builtin commands
 * supported by the shell.
 *
 * @param simple_cmd The command to check
 * @return int Returns 1 if the command is a builtin, 0 otherwise
 */
int is_builtin(const char *word)
{
    const char *builtins[7];
    int i = 0;

    i=0;
    builtins[0] = "echo";
    builtins[1] = "cd";
    builtins[2] = "pwd";
    builtins[3] = "export";
    builtins[4] = "unset";
    builtins[5] = "env";
    builtins[6] = NULL;
    while (builtins[i])
    {
        if (ft_strcmp(word, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

/**
 * @brief Execute a builtin command
 *
 * This function executes the appropriate builtin command based on the
 * command name. It handles echo, cd, pwd, export, unset, and env commands.
 *
 * @param args Array of command arguments
 * @param env Pointer to the environment structure
 * @return int Returns the exit status of the builtin command
 */
int execute_builtin(char **args, t_env **env, t_ntc **first_node)
{
    int word_count;

    word_count = count_words(args);
    if (ft_strcmp(args[0], "echo") == 0)
        return (builtin_echo(args, word_count, first_node));
    else if (ft_strcmp(args[0], "cd") == 0)
        return (builtin_cd(args, env, first_node));
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (builtin_pwd(args, first_node));
    else if (ft_strcmp(args[0], "export") == 0)
    {
        builtin_export(args, env, first_node);
        //print_env(*env);
    }
    else if (ft_strcmp(args[0], "unset") == 0)
        return (builtin_unset(args, env));
    else if (ft_strcmp(args[0], "env") == 0)
        return (builtin_env(args, env, first_node));
    return 1;
}


/*
Below is the current implementation of the execute_command function. Would be discarded in favor of the new implementation.

char	*execute_command(t_astnode *node, t_ntc **first_node, char **env)
{
	if (!node)
		return (NULL);
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "cd") == 0)
		builtin_cd(node, first_node, env);
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "export") == 0)
		builtin_export(node, first_node, env);
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "unset") == 0)
		builtin_unset(node, first_node);
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "echo") == 0)
		return (builtin_echo(node, first_node));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "pwd") == 0)
		return (builtin_pwd(first_node));
	if (node->data.simple_cmd.words && \
		ft_strcmp(node->data.simple_cmd.words->data.word.value, "env") == 0)
		return (builtin_env(env, first_node));
	return (NULL);
}*/