#include "minishell.h"


/*
 * Checks if the given token type is a word token.
 * Returns 1 if it is, 0 otherwise.
 */
static int is_word_token(t_token_type type) 
{
    //printf("is_word_token start\n");
    //printf("is_word_token end\n");
    return (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE || 
            type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR ||
            type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD ||
            type == TOKEN_WORD);
}

/* 
 * Checks if the given token type is a redirection token.
 * Returns 1 if it is, 0 otherwise.
 */
static int is_redirection_token(t_token_type type) 
{
    //printf("is_redirection_token start\n");
    //printf("is_redirection_token end\n");
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
            type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}

/* 
 * Parses a list of redirections.
 * Returns the head of a linked list of redirection nodes.
 */
static t_astnode *parse_redirection_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns, t_astnode **last_word) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *redir_node;
    
    //printf("parse_redirection_list start\n");
    head = NULL;
    current = NULL;
    while (is_redirection_token(c_tkn->type)) 
    {
        redir_node = create_ast_node(first_node, NODE_REDIRECTION);
        redir_node->data.redirection.type = c_tkn->type;
        c_tkn = get_next_token(tkns, 1);
        if (!is_word_token(c_tkn->type))
        {
            fprintf(stderr, "Error: Expected filename after redirection\n");
            exit(1);
        }
        redir_node->data.redirection.file = c_tkn->value; //ft_strdup_g_c(c_tkn->value, first_node);
        c_tkn = get_next_token(tkns, 1);
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
        if (is_word_token(c_tkn->type))
            (*last_word)->data.word.next = parse_word_list(first_node, c_tkn, tkns, last_word);
    }
    if (current)
        current->data.redirection.next = NULL;
    //printf("parse_redirection_list end\n");
    return (head);
}

/* 
 * Parses a list of words (cmd and its arguments).
 * Returns the head of a linked list of word nodes.
 */
t_astnode *parse_word_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns, t_astnode **last_word) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *word_node;

    head = NULL;
    current = NULL;
    while (c_tkn && is_word_token(c_tkn->type)) 
    {
        word_node = create_ast_node(first_node, NODE_WORD);
        word_node->data.word.value = c_tkn->value; //ft_strdup_g_c(c_tkn->value, first_node);//this might be unnecessary as I don't think we need to recreate a malloc for this token as it is already stored int the tkns** array.
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
        c_tkn = get_next_token(tkns, 1);
    }
    if (current)
    {
        *last_word = current;
        current->data.word.next = NULL;
    }
    t_astnode *temp = head;
    while (temp)
    {
        temp = temp->data.word.next;
    }
    return (head);
}

/* 
 * Parses a simple cmd, which consists of a word list (cmd and its arguments)
 * and an optional list of redirections.
 * Returns a node representing the simple cmd.
 */
static t_astnode *parse_simple_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    t_astnode *last_word;
    
    //printf("parse_simple_cmd start\n");
    node = create_ast_node(first_node, NODE_SIMPLE_CMD);
    //if (c_tkn)
    //{
     //   printf("c_tkn->type: %s\n", c_tkn->value);
    //}
    node->data.simple_cmd.words = parse_word_list(first_node, c_tkn, tkns, &last_word);
    node->data.simple_cmd.redirections = parse_redirection_list(first_node, c_tkn, tkns, &last_word);
    //printf("parse_simple_cmd end\n");
    return (node);
}

/* 
 * Parses a cmd, which can be either a simple cmd or a cmd line
 * enclosed in parentheses.
 * Returns a node representing the cmd.
 */
static t_astnode *parse_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;

    //printf("parse_cmd start\n");
    if (c_tkn->type == TOKEN_LPAREN) 
    {
        c_tkn = get_next_token(tkns, 1);
        node = parse_cmd_line(first_node, c_tkn, tkns);
        if (c_tkn->type != TOKEN_RPAREN) 
        {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(1);
        }
        c_tkn = get_next_token(tkns, 1);
        //printf("parse_cmd end\n");
        return (node);
    } 
    else 
    {
        //printf("parse_cmd end\n");
        return parse_simple_cmd(first_node, c_tkn, tkns);
    }
}

/* 
 * Parses a pipeline, which is a sequence of cmds connected by pipes (|).
 * Returns a node representing the pipeline.
 */
static t_astnode *parse_pipeline(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    
    //printf("parse_pipeline start\n");
    node = create_ast_node(first_node, NODE_PIPELINE);
    node->data.pipeline.cmds = g_c(first_node, sizeof(t_astnode*))->data;
    node->data.pipeline.cmds[0] = parse_cmd(first_node, c_tkn, tkns);
    node->data.pipeline.cmd_count = 1;
    
    while (c_tkn->type == TOKEN_PIPE) 
    {
        c_tkn = get_next_token(tkns, 1);
        node->data.pipeline.cmd_count++;
        /*node->data.pipeline.cmds = ft_realloc_g_c(first_node,\
                                        node->data.pipeline.cmds,\
                                        node->data.pipeline.cmd_count\
                                        * sizeof(t_astnode*));*/
        node->data.pipeline.cmds = realloc(node->data.pipeline.cmds,\
                                        node->data.pipeline.cmd_count\
                                        * sizeof(t_astnode*));
        node->data.pipeline.cmds[node->data.pipeline.cmd_count - 1]\
                                = parse_cmd(first_node, c_tkn, tkns);
    }
    //printf("parse_pipeline end\n");
    return (node);
}

/* 
 * Parses a cmd line, which can be a single pipeline or multiple pipelines
 * connected by AND (&&) or OR (||) operators.
 * Returns the root node of the parsed cmd line.
 */
t_astnode *parse_cmd_line(t_ntc **first_node, t_token *c_tkn, t_token **tkns) 
{
    t_astnode *node;
    t_astnode *new_node;
    
    //printf("parse_cmd_line start\n");
    node = parse_pipeline(first_node, c_tkn, tkns);
    while (c_tkn->type == TOKEN_AND || c_tkn->type == TOKEN_OR) 
    {
        new_node = create_ast_node(first_node, NODE_CMD_LINE);
        new_node->data.cmd_line.left = node;
        new_node->data.cmd_line.operator = c_tkn->type;
        c_tkn = get_next_token(tkns, 1);
        new_node->data.cmd_line.right = parse_pipeline(first_node, c_tkn, tkns);
        node = new_node;
    }
    //printf("parse_cmd_line end\n");
    return (node);
}