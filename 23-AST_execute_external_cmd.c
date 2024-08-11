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

static int	get_env_var(t_env **env, const char *name, char **value)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = strlen(name);
	while ((*env)->var[i])
	{
		if (strncmp((*env)->var[i], name, name_len) == 0
			&& (*env)->var[i][name_len] == '=')
		{
			*value = (*env)->var[i] + name_len + 1;
			return (i);
		}
		i++;
	}
	*value = NULL;
	return (-1);
}

char *join_path(const char *path, const char *cmd)
{
    char *full_path;
    int len;

    len = strlen(path) + strlen(cmd) + 2;
    full_path = (char *)malloc(len);
    if (!full_path)
        return (NULL);
    strcpy(full_path, path);
    strcat(full_path, "/");
    strcat(full_path, cmd);
    return (full_path);
}

char *find_command_path(char *cmd, t_env **env, t_ntc **first_node)
{
    char **paths;
    char *path_env;
    char *cmd_path;
    int i;

    if (get_env_var(env, "PATH", &path_env) == -1 || !path_env)
        return (NULL);
    paths = ft_split(path_env, ':', first_node);  // Assuming ft_split exists
    i = 0;
    while (paths[i])
    {
        cmd_path = join_path(paths[i], cmd);
        if (access(cmd_path, X_OK) == 0)
        {
            //free(paths);  // Free the paths array
            return (cmd_path); // Found the command
        }
        //free(cmd_path);
        i++;
    }
    //free(paths);  // Free the paths array
    return (NULL); // Command not found
}

int execute_external_cmd(char **words_arr, t_env **env, t_ntc **first_node)
{
    pid_t pid;
    char *command_path;
    int status;
    
    if (words_arr[0][0] == '/' || words_arr[0][0] == '.' || words_arr[0][0] == '~')
        command_path = strdup(words_arr[0]);
    else
        command_path = find_command_path(words_arr[0], env, first_node);
    if (!command_path)
    {
        printf("command not found: %s\n", words_arr[0]);
        return (1);
    }
    pid = fork_process();
    if (pid == 0)
    {
        execve(command_path, words_arr, (*env)->var);
        perror("execve");
        exit(1);
    }
    else
    {
        waitpid(pid, &status, 0);
        return (WEXITSTATUS(status));
    }
}