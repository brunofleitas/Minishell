#include "minishell.h"

/**
 @brief Main execution function for the AST

 This function serves as the entry point for executing the Abstract Syntax Tree (AST).
 It determines the type of the node and calls the appropriate execution function.

 @param node Pointer to the current AST node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the executed command
*/
int execute_ast(t_astnode *node, t_env *env, t_ntc **first_node)
{
    if (!node)
        return (0);
    if (node->type == NODE_CMD_LINE)
        return (execute_cmd_line(node, env, first_node));
    else if (node->type == NODE_PIPELINE)
        return (execute_pipeline(node, env, first_node));
    else if (node->type == NODE_SIMPLE_CMD)
        return (execute_simple_cmd(node, env, first_node));
    else
    {
        printf("%i\n", node->type);
        ft_putstr_fd("Error: Unknown node type\n", STDERR_FILENO);// just an Idea I got if we want a file where we store all the errors
        return (1);
    }
}

/**
 @brief Execute a command line node
 This function handles the execution of a command line node, which can contain
 multiple commands connected by AND (&&) or OR (||) operators.

 @param node Pointer to the command line node
 @param env Pointer to the environment structure
 @return int Returns the exit status of the last executed command
 */
int execute_cmd_line(t_astnode *node, t_env *env, t_ntc **first_node)
{
    int left_result;
    
    left_result = execute_ast(node->data.cmd_line.left, env, first_node);
    if (node->data.cmd_line.operator == TOKEN_AND)
    {
        if (left_result == 0)
            return (execute_ast(node->data.cmd_line.right, env, first_node));
        return left_result;
    }
    else if (node->data.cmd_line.operator == TOKEN_OR)
    {
        if (left_result != 0)
            return (execute_ast(node->data.cmd_line.right, env, first_node));
        return left_result;
    }
    return (left_result);
}