#include "minishell.h"

static void print_ast(t_astnode *node, int indent) {
    if (!node) return;
    
    // Indentation for readability
    for (int i = 0; i < indent; ++i) printf("  ");

    switch (node->type) {
        case NODE_CMD_LINE:
            ft_printf("Command Line:\n");
            print_ast(node->data.cmd_line.left, indent + 1);
            break;
        case NODE_PIPELINE:
            ft_printf("Pipeline:\n");
            for (int i = 0; node->data.pipeline.cmds[i]; ++i) {
                print_ast(node->data.pipeline.cmds[i], indent + 1);
            }
            break;
        case NODE_SIMPLE_CMD:
            ft_printf("Simple Command:\n");
            t_astnode *current = node->data.simple_cmd.words;
            while (current) {
                print_ast(current, indent + 1);
                current = current->data.word.next;
            }
            break;
        case NODE_WORD:
            ft_printf("Word: %s\n", node->data.word.value);
            break;
        case NODE_REDIRECTION:
            ft_printf("Redirection: filename=%s, type=%d\n", node->data.redirection.file, node->data.redirection.type);
            break;
        default:
            ft_printf("Unknown node type: %d\n", node->type);
            break;
    }
}

t_astnode *parser(t_ntc **first_node, t_token **tkns) 
{
    t_token     *c_tkn;
    t_astnode   *cmd_line;
    /*t_astnode   *pipeline;
    t_astnode   *simple_cmd;
    t_astnode   *current;*/

    c_tkn = get_next_token(tkns); // Initialize c_tkn
    cmd_line = parse_cmd_line(first_node, c_tkn, tkns);
    print_ast(cmd_line, 0);
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