#include "minishell.h"

// static void throw_error(int p_name, char *exit_code, char *cmd, t_ma *ma);
// static void stop_child_or_parent(int exit_code, t_ma *ma);


// /// @brief 
// /// @param ec stands for "error code". It can be NULL, "00", "01", "10" or "11". If an  "m" is present in the string, the function will print "minishell: " before the error message. The first number of the error code correspond
// /// @param exit_code is the exit code that will be sent by the function if the error code is "10" or "11".
// /// @param cmd_ao_error 
// /// @param ma 
// void exit_or_setexit(char *ec, char *exit_code, char *cmd_ao_error, t_ma *ma)
// {
//     int p_name;

//     p_name = 0;
//     if (!ec || ft_strlen(ec) < 2)
//     {
//         ft_putstr_fd("1: exit_or_setexit: invalid length or missing \"ec\"", 2);
//         stop_child_or_parent(EXIT_FAILURE, ma);
//         return;
//     }
//     if ((ec[0] < '0' || ec[0] > '1') || (ec[1] < '0' || ec[1] > '1'))
//     {
//         ft_putstr_fd("1: exit_or_setexit: invalid value \"ec\"", 2);
//         stop_child_or_parent(EXIT_FAILURE, ma);
//         return;
//     }
//     if (ec[2] && ec[2] == "m")
//         p_name = 1;
//     else if (ec[2])
//     {
//         ft_putstr_fd("1: exit_or_setexit: invalid \"ec\"", 2);
//         stop_child_or_parent(EXIT_FAILURE, ma);
//         return;
//     }
//     if (ft_strncmp(ec, "00", 2) == 0)
//     {
//         stop_child_or_parent(EXIT_SUCCESS, ma);
//         return;
//     }
//     if (ft_strcmp(ec, "01") == 0) // is usefull for exemple when an input redireciton fails but the command successfully executed regardless because the redirectionfail wasn't critical for the command execution
//     {
//         throw_error(NULL, EXIT_SUCCESS, cmd_ao_error, ma);
//         stop_child_or_parent(EXIT_SUCCESS, ma);
//         return;
//     }
//     if ((ft_strncmp(ec, "1", 1) == 0) && !exit_code)
//     {
//         throw_error(NULL, EXIT_FAILURE, "exit_or_setexit: missing \"exit_code\"", ma);
//         stop_child_or_parent(EXIT_FAILURE, ma);
//         return;
//     }
//     if (ft_strncmp(ec, "10", 2) == 0)
//             stop_child_or_parent(ft_atoi(exit_code), ma);
//     else if (ft_strncmp(ec, "11", 2) == 0 && exit_code)
//     {
//         if(!cmd_ao_error)
//         {
//             ft_putstr_fd("1: exit_or_setexit: missing \"cmd_ao_error\"", 2);
//             stop_child_or_parent(EXIT_FAILURE, ma);
//         }
//         else
//         {
//             throw_error(p_name, exit_code, cmd_ao_error, ma);
//             stop_child_or_parent(ft_atoi(exit_code), ma);
//         }
//         return;
//     }
// }
// cmd_ao_error stands for command and/or error

static void throw_error(int p_name, char *exit_code, char *cmd_ao_error, t_ma *ma)
{
    if (p_name)
        ft_putstr_fd("minishell: ", 2);
    if (exit_code)
        ft_putstr_fd(exit_code, 2);
        ft_putstr_fd(": ", 2);
    if (cmd_ao_error)
    {
        if(ft_strcmp(cmd_ao_error, "perror") == 0)
            perror(" ");
        else
            ft_putstr_fd(cmd_ao_error, 2);
    }
    perror(" ");
}

static void stop_child_or_parent(int exit_code, t_ma *ma)
{
    if (ma->in_child_p)
        exit(exit_code);
    else
        ma->last_exit_status = exit_code;
}

void    exit_setexit()
{
    arr[]
}
