#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    while (1)
    {
        char *input = NULL;
        input = readline(">>");
        if (strcmp(input, "") != 0)      
        {
            write(1, "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<\n", 44);
            //write(2, "> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<\n", 44);
            //fflush(stdout);
            exit(0);
        }
        else if (strcmp(input, "exit") == 0)
        {
            free(input);
            exit(0);
        }
        free(input);
    }
    exit (0);
}