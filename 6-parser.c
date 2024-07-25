#include "minishell.h"

t_astnode *parser(t_ntc **first_node, t_token **tkns) 
{
    t_token     *c_tkn;
    t_astnode   *cmd_line;
    /*t_astnode   *pipeline;
    t_astnode   *simple_cmd;
    t_astnode   *current;*/

    c_tkn = get_next_token(tkns); // Initialize c_tkn
    cmd_line = parse_cmd_line(first_node, c_tkn, tkns);
    // Print the parsed words in the first simple cmd
    /*if (cmd_line->type == NODE_CMD_LINE) 
    {
        pipeline = cmd_line->data.cmd_line.left;
        if (pipeline->type == NODE_PIPELINE) 
        {
            simple_cmd = pipeline->data.pipeline.cmds[0];
            current = simple_cmd->data.simple_cmd.words;
            while (current) 
            {
                printf("Word: %s\n", current->data.word.value);
                current = current->data.word.next;
            }*
        }
    } 
    else if (cmd_line->type == NODE_PIPELINE) 
    {
        simple_cmd = cmd_line->data.pipeline.cmds[0];
        current = simple_cmd->data.simple_cmd.words;
        while (current) 
        {
            printf("Word: %s\n", current->data.word.value);
            current = current->data.word.next;
        }
    }
    else 
    {
        // Handle unexpected type (for robustness)
        fprintf(stderr, "Error: Unexpected node type\n");
    }
    */
    return cmd_line;
}