#include "minishell.h"



t_token current_token;
t_token get_next_token();

t_astnode *create_ast_node(t_ntc **first_node, t_nodetype type) 
{
    t_astnode *node;
    
    node = gc(first_node, sizeof(t_astnode));
    if (!node) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    node->next = NULL;
    return (node);
}

/* 
 * Parses a command line, which can be a single pipeline or multiple pipelines
 * connected by AND (&&) or OR (||) operators.
 * Returns the root node of the parsed command line.
 */
t_astnode *parse_command_line(t_ntc **first_node) 
{
    t_astnode *node;
    t_astnode *new_node;
    
    node = parse_pipeline(first_node);
    while (current_token.type == TOKEN_AND || current_token.type == TOKEN_OR) 
    {
        new_node = create_ast_node(first_node, NODE_COMMAND_LINE);
        new_node->data.command_line.left = node;
        new_node->data.command_line.operator = current_token.type;
        get_next_token();
        new_node->data.command_line.right = parse_pipeline(first_node);
        node = new_node;
    }
    
    return (node);
}

/* 
 * Parses a pipeline, which is a sequence of commands connected by pipes (|).
 * Returns a node representing the pipeline.
 */
t_astnode *parse_pipeline(t_ntc **first_node) 
{
    t_astnode *node;
    
    node = create_ast_node(first_node, NODE_PIPELINE);
    node->data.pipeline.commands = gc(first_node, sizeof(t_astnode*));
    node->data.pipeline.commands[0] = parse_command(first_node);
    node->data.pipeline.command_count = 1;
    
    while (current_token.type == TOKEN_PIPE) 
    {
        get_next_token();
        node->data.pipeline.command_count++;
        node->data.pipeline.commands = realloc(node->data.pipeline.commands, 
                                               node->data.pipeline.command_count * sizeof(t_astnode*));
        node->data.pipeline.commands[node->data.pipeline.command_count - 1] = parse_command(first_node);
    }
    
    return (node);
}

/* 
 * Parses a command, which can be either a simple command or a command line
 * enclosed in parentheses.
 * Returns a node representing the command.
 */
t_astnode *parse_command(t_ntc **first_node) 
{
    t_astnode *node;

    if (current_token.type == TOKEN_LPAREN) 
    {
        get_next_token();
        node = parse_command_line(first_node);
        if (current_token.type != TOKEN_RPAREN) {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(1);
        }
        get_next_token();
        return (node);
    } else 
    {
        return parse_simple_command(first_node);
    }
}

/* 
 * Parses a simple command, which consists of a word list (command and its arguments)
 * and an optional list of redirections.
 * Returns a node representing the simple command.
 */
t_astnode *parse_simple_command(t_ntc **first_node) 
{
    t_astnode *node;
    
    node = create_ast_node(first_node, NODE_SIMPLE_COMMAND);
    node->data.simple_command.words = parse_word_list(first_node);
    node->data.simple_command.redirections = parse_redirection_list(first_node);
    return (node);
}

/* 
 * Parses a list of words (command and its arguments).
 * Returns the head of a linked list of word nodes.
 */
t_astnode *parse_word_list(t_ntc **first_node) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *word_node;

    head = NULL;
    current = NULL;
    while (is_word_token(current_token.type)) 
    {
        word_node = create_ast_node(first_node, NODE_WORD);
        word_node->data.word.value = strdup(current_token.value);
        word_node->data.word.type = current_token.type;

        if (!head) {
            head = word_node;
            current = head;
        } else {
            current->next = word_node;
            current = word_node;
        }

        get_next_token();
    }

    return (head);
}

/* 
 * Parses a list of redirections.
 * Returns the head of a linked list of redirection nodes.
 */
t_astnode *parse_redirection_list(t_ntc **first_node) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *redir_node;
    
    head = NULL;
    current = NULL;
    while (is_redirection_token(current_token.type)) 
    {
        redir_node = create_ast_node(first_node, NODE_REDIRECTION);
        redir_node->data.redirection.type = current_token.type;
        get_next_token();
        if (!is_word_token(current_token.type)) {
            fprintf(stderr, "Error: Expected filename after redirection\n");
            exit(1);
        }
        redir_node->data.redirection.file = strdup(current_token.value);
        get_next_token();
        
        if (!head) {
            head = redir_node;
            current = head;
        } else {
            current->next = redir_node;
            current = redir_node;
        }
    }
    return (head);
}

/* 
 * Checks if the given token type is a word token.
 * Returns 1 if it is, 0 otherwise.
 */
int is_word_token(t_token_type type) 
{
    return (type == TOKEN_WORD || type == TOKEN_SINGLE_QUOTE || type == TOKEN_DOUBLE_QUOTE ||
           type == TOKEN_ENV_VAR || type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD);
}

/* 
 * Checks if the given token type is a redirection token.
 * Returns 1 if it is, 0 otherwise.
 */
int is_redirection_token(t_token_type type) 
{
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || 
           type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}