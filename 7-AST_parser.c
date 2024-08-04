#include "minishell.h"

t_astnode *parser(t_ntc **first_node, t_token **tkns) 
{
    t_token     *c_tkn;
    t_astnode   *cmd_line;

    c_tkn = NULL;
    c_tkn = get_next_token(tkns, 1);
    printf("get_next_token\n");
    cmd_line = parse_cmd_line(first_node, c_tkn, tkns);
    return (cmd_line);
}