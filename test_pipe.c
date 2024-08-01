#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv, char **envp)  
{
    int fd[2];
    pipe(fd);
    if (fork() == 0) 
    {
        close(fd[0]);
        write(fd[1], "Hello from child\n", 17);
        close(fd[1]);
    } else {
        close(fd[1]);
        char buffer[20];
        read(fd[0], buffer, 17);
        buffer[17] = '\0';
        printf("Parent received: %s", buffer);
        close(fd[0]);
    }
    return 0;
}