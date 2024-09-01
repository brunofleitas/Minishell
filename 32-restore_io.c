
#include "minishell.h"

/**
 *  * @brief Restore the standard I/O to their original state
 *
 * This function restores the standard input and output to their saved states.
 *
 * @param saved_stdin The saved standard input file descriptor
 * @param saved_stdout The saved standard output file descriptor
*/
void restore_io(t_ma *ma)
{
    dup2(ma->saved_stdin, STDIN_FILENO);
    dup2(ma->saved_stdout, STDOUT_FILENO);
}
