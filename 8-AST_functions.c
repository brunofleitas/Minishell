#include "minishell.h"

/* 
 * Parses a cmd line, which can be a single pipeline or multiple pipelines
 * connected by AND (&&) or OR (||) operators.
 * Returns the root node of the parsed cmd line.
 */
t_astnode *parse_cmd_line(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    t_astnode *new_node;
    
    node = parse_pipeline(first_node, c_tkn, tkns);
    while (c_tkn->type == TOKEN_AND || c_tkn->type == TOKEN_OR) 
    {
        new_node = create_ast_node(first_node, NODE_CMD_LINE);
        new_node->data.cmd_line.left = node;
        new_node->data.cmd_line.operator = c_tkn->type;
        c_tkn = get_next_token(tkns);
        new_node->data.cmd_line.right = parse_pipeline(first_node, c_tkn, tkns);
        node = new_node;
    }
    return (node);
}

/* 
 * Parses a pipeline, which is a sequence of cmds connected by pipes (|).
 * Returns a node representing the pipeline.
 */
t_astnode *parse_pipeline(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    
    node = create_ast_node(first_node, NODE_PIPELINE);
    node->data.pipeline.cmds = g_c(first_node, sizeof(t_astnode*))->data;
    node->data.pipeline.cmds[0] = parse_cmd(first_node, c_tkn, tkns);
    node->data.pipeline.cmd_count = 1;
    
    while (c_tkn->type == TOKEN_PIPE) 
    {
        c_tkn = get_next_token(tkns);
        node->data.pipeline.cmd_count++;
        node->data.pipeline.cmds = ft_realloc_g_c(first_node,\
                                        node->data.pipeline.cmds,\
                                        node->data.pipeline.cmd_count\
                                        * sizeof(t_astnode*));
        node->data.pipeline.cmds[node->data.pipeline.cmd_count - 1]\
                                = parse_cmd(first_node, c_tkn, tkns);
    }
    return (node);
}

/* 
 * Parses a cmd, which can be either a simple cmd or a cmd line
 * enclosed in parentheses.
 * Returns a node representing the cmd.
 */
t_astnode *parse_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;

    if (c_tkn->type == TOKEN_LPAREN) 
    {
        c_tkn = get_next_token(tkns);
        node = parse_cmd_line(first_node, c_tkn, tkns);
        if (c_tkn->type != TOKEN_RPAREN) 
        {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(1);
        }
        c_tkn = get_next_token(tkns);
        return (node);
    } 
    else 
    {
        return parse_simple_cmd(first_node, c_tkn, tkns);
    }
}

/* 
 * Parses a simple cmd, which consists of a word list (cmd and its arguments)
 * and an optional list of redirections.
 * Returns a node representing the simple cmd.
 */
t_astnode *parse_simple_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    
    node = create_ast_node(first_node, NODE_SIMPLE_CMD);
    node->data.simple_cmd.words = parse_word_list(first_node, c_tkn, tkns);
    node->data.simple_cmd.redirections = parse_redirection_list(first_node, c_tkn, tkns);
    return (node);
}

/* 
 * Parses a list of words (cmd and its arguments).
 * Returns the head of a linked list of word nodes.
 */
t_astnode *parse_word_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *word_node;

    head = NULL;
    current = NULL;
    while (is_word_token(c_tkn->type)) 
    {
        word_node = create_ast_node(first_node, NODE_WORD);
        word_node->data.word.value = ft_strdup_g_c(c_tkn->value, first_node);
        word_node->data.word.type = c_tkn->type;

        if (!head) 
        {
            head = word_node;
            current = head;
        }
        else
        {
            current->data.word.next = word_node;
            current = word_node;
        }

        c_tkn = get_next_token(tkns);
    }
    return (head);
}

/* 
 * Parses a list of redirections.
 * Returns the head of a linked list of redirection nodes.
 */
t_astnode *parse_redirection_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *redir_node;
    
    head = NULL;
    current = NULL;
    while (is_redirection_token(c_tkn->type)) 
    {
        redir_node = create_ast_node(first_node, NODE_REDIRECTION);
        redir_node->data.redirection.type = c_tkn->type;
        c_tkn = get_next_token(tkns);
        if (!is_word_token(c_tkn->type))
        {
            fprintf(stderr, "Error: Expected filename after redirection\n");
            exit(1);
        }
        redir_node->data.redirection.file = ft_strdup_g_c(c_tkn->value, first_node);
        c_tkn = get_next_token(tkns);
        if (!head) 
        {
            head = redir_node;
            current = head;
        }
        else
        {
            current->data.redirection.next = redir_node;
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
    return (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE || 
            type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR ||
            type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD);
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