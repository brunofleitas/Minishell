#include "minishell.h"

int execute_external_cmd(char **words_arr, t_ma *ma)
{
    pid_t pid;
    
    (void)words_arr;
    (void)ma;
    pid = fork_process();
    if (pid == 0)
    {
        //execve(words_arr[0], words_arr, env->var);
        perror("execve");
        exit(1);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
        return (WEXITSTATUS(status));
    }
}