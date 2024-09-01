#include "minishell.h"

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

static char	*get_n_token(const char **s, char c, t_ntc **first_node)
{
	const char	*start;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	return (ft_substr_g_c(start, 0, *s - start, first_node));
}

static char	**ft_split(char const *s, char c, t_ntc **first_node)
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
		split[i++] = get_n_token(&s, c, first_node);
	split[i] = NULL;
	return (split);
}

//CHECK WHY SPLITS ARE NOT WORKING


char *join_path(const char *path, const char *cmd, t_ntc **first_node)
{
    char *full_path;
    int len;
    int len_path;
    int len_cmd;

    len_path = ft_strlen(path);
    len_cmd = ft_strlen(cmd);
    len = len_path + len_cmd + 2;
    full_path = g_c(first_node, sizeof(char) * len)->data;   
    if (!full_path)
        return (NULL);
    ft_strlcpy(full_path, path, len);
    ft_strlcat(full_path, "/", len);
    ft_strlcat(full_path, cmd, len);
    return (full_path);
}

static char *find_command_path(char *cmd, t_env **env, int *p_ue, t_ntc **first_node)
{
    char **paths;
    char *path_env;
    char *cmd_path;
    int i;
   
    if (get_env_var(env, "PATH", &path_env) == -1)
    {
        *p_ue = 1;
        return (NULL);
    }
    paths = ft_split(path_env, ':', first_node);  // Assuming ft_split exists
    i = 0;
    while (paths[i])
    {
        cmd_path = join_path(paths[i], cmd, first_node);
        if (access(cmd_path, X_OK) == 0)
        {
            //free(paths);  // Free the paths array
            return (cmd_path); // Found the command
        }
        //free(cmd_path);
        i++;
    }
    //free(paths);  // Free the paths array
    return (NULL); // Command not found or path was not set, if the path was unset then the shell checks if the command that was not found is a file in the current directory.
}

void execute_external_cmd(char **words_arr, t_env **env, t_ntc **first_node)
{
    // pid_t pid;
    char *command_path;
    // int status;
    // char **current;
    struct stat path_stat;
    int    p_ue; // flag added to check if path was unset or empty
    // Check if the command is empty
    p_ue = 0;
    command_path = NULL;
    // printf("words_arr[0]: %s\n", words_arr[0]);
    // printf("words_arr[0][0]: %c\n", words_arr[0][0]);
    if (words_arr == NULL || words_arr[0] == NULL || words_arr[0][0] == '\0')
    {
        exit (0);  // Return 0 for an empty command
    }
    // current = words_arr;
    // while (*current)
    // {
    //     printf("word: %s\n", *words_arr);
    //     current++;
    // }
    if (words_arr[0][0] == '/' || words_arr[0][0] == '.' || words_arr[0][0] == '~')
        command_path = ft_strdup_g_c(words_arr[0], first_node);
    else
    {
        // ft_printf("find_command_path_start\n");
        command_path = find_command_path(words_arr[0], env, &p_ue, first_node);
        // ft_printf("find_command_path_end\n");
    }
    // ft_printf("command_path: %s\n", command_path);
    
    // Check if command_path was found
    if (p_ue)
    {
        if (access(words_arr[0], F_OK) != 0)
        {
            // perror("minishell: ");
            write(2, "minishell: ", 11);
            write(2, words_arr[0], ft_strlen(words_arr[0]));
            write(2, ": No such file or directory\n", 28);
            exit(127);  // Return 127 for "No such file or directory"
        }
        if (access(words_arr[0], X_OK) != 0)
        {
            write(2, "minishell: ", 11);
            write(2, words_arr[0], ft_strlen(words_arr[0]));
            write(2, ": Permission denied\n", 20);
            exit(126);  // Return 126 for "Permission denied"
        }
    }
    if (!command_path)
    {
        // write(2, " command not found\n", 19);
        write(2, "minishell: ", 11);
        write(2, words_arr[0], ft_strlen(words_arr[0]));
        write(2, ": command not found\n", 20);
        exit(127);  // Return 127 if the command was not found
    }

    // Check if the path is a directory
    if (stat(command_path, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
    {
        // perror("minishell: ");
        write(2, "minishell: ", 11);
        write(2, command_path, ft_strlen(command_path));
        write(2, ": Is a directory\n", 17);
        exit(126);  // Return 126 if the path is a directory
    }

    // Check if the file exists
    if (access(command_path, F_OK) != 0)
    {
        // perror("minishell: ");
        write(2, "minishell: ", 11);
        write(2, command_path, ft_strlen(command_path));
        write(2, ": No such file or directory\n", 28);
        exit(127);  // Return 127 for "No such file or directory"
    }

    // Check if the file is executable
    if (access(command_path, X_OK) != 0)
    {
        write(2, "minishell: ", 11);
        write(2, command_path, ft_strlen(command_path));
        write(2, ": Permission denied\n", 20);
        exit(126);  // Return 126 for "Permission denied"
    }

    exit(execve(command_path, words_arr, (*env)->var));
    
}
