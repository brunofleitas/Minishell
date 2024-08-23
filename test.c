#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    while (1)
    {
        printf(">>");
        char *input = NULL;
        size_t len = 0;
        ssize_t read = getline(&input, &len, stdin);
        if (read == -1) {
            if (errno == 0) {
                // EOF detected
                break;
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        if (input[0] != '\n')
        {
            printf("> >> < * ? [ ] | ; [ ] || && ( ) & # $  <<\n");
        }
        free(input);
    }
    return 0;
}