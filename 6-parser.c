#include <minishell.h>

t_astnode *parser(t_ntc **first_node) 
{
    t_token     current_token; // Static variable to maintain token state
    t_astnode   *command_line;
    t_astnode   *pipeline;
    t_astnode   *simple_command;
    t_astnode   *current;

    current_token = get_next_token(); // Initialize current_token
    command_line = parse_command_line(first_node, &current_token);
    // Print the parsed words in the first simple command
    if (command_line->type == NODE_COMMAND_LINE) 
    {
        pipeline = command_line->data.command_line.left;
        if (pipeline->type == NODE_PIPELINE) 
        {
            simple_command = pipeline->data.pipeline.commands[0];
            current = simple_command->data.simple_command.words;
            /*while (current) 
            {
                printf("Word: %s\n", current->data.word.value);
                current = current->data.word.next;
            }*/
        }
    } 
    else if (command_line->type == NODE_PIPELINE) 
    {
        simple_command = command_line->data.pipeline.commands[0];
        current = simple_command->data.simple_command.words;
        /*while (current) 
        {
            printf("Word: %s\n", current->data.word.value);
            current = current->data.word.next;
        }*/
    } 
    else 
    {
        // Handle unexpected type (for robustness)
        fprintf(stderr, "Error: Unexpected node type\n");
    }
    return command_line;
}