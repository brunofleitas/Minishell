/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9-AST_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:08:01 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/13 17:17:59 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
 * Checks if the given token type is a word token.
 * Returns 1 if it is, 0 otherwise.
 */
/*
static int is_word_token(t_token_type type) 
{
    //printf("is_word_token start\n");
    //printf("is_word_token end\n");
    return (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE || 
            type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR ||
            type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD ||
            type == TOKEN_WORD);
}*/

static int is_word_token(t_token_type type) 
{
    //printf("is_word_token start: type = %d\n", type);

    int result = (type == TOKEN_BUILTIN || type == TOKEN_SINGLE_QUOTE || 
                 type == TOKEN_DOUBLE_QUOTE || type == TOKEN_ENV_VAR ||
                 type == TOKEN_EXIT_STATUS || type == TOKEN_WILDCARD ||
                 type == TOKEN_WORD);

    //printf("is_word_token end: result = %d\n", result);
    return result;
}

/* 
 * Checks if the given token type is a redirection token.
 * Returns 1 if it is, 0 otherwise.
 */
/*
static int is_redirection_token(t_token_type type) 
{
    //printf("is_redirection_token start\n");
    //printf("is_redirection_token end\n");
    return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
            type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);
}*/
static int is_redirection_token(t_token_type type) 
{
    //printf("is_redirection_token start: type = %d\n", type);

    int result = (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT ||
                 type == TOKEN_REDIR_APPEND || type == TOKEN_HEREDOC);

    //printf("is_redirection_token end: result = %d\n", result);
    return result;
}

/* 
 * Parses a list of words (cmd and its arguments).
 * Returns the head of a linked list of word nodes.
 */
static t_astnode *parse_word_list(t_astnode **last_word, t_ma *ma) 
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *word_node;
    t_astnode *temp;

    //printf("parse_word_list start\n");
    head = NULL;
    current = NULL;
    while ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type)) 
    {
        word_node = create_ast_node(&(ma->first_node), NODE_WORD);
        word_node->data.word.value = (*(ma->c_tkn))->value; 
        word_node->data.word.type = (*(ma->c_tkn))->type;
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
        get_next_token(ma);
    }
    if (current)
    {
        *last_word = current;
        current->data.word.next = NULL;
    }
    temp = head;
    while (temp)
    {
        temp = temp->data.word.next;
    }
    //printf("parse_word_list end\n");
    return (head);
}

/* 
 * Parses a list of redirections.
 * Returns the head of a linked list of redirection nodes.
 */
static t_astnode *parse_redirection_list(t_astnode **last_word, t_ma *ma)
{
    t_astnode *head;
    t_astnode *current;
    t_astnode *redir_node;
    
    //printf("parse_redirection_list start\n");
    head = NULL;
    current = NULL;
    while ((*(ma->c_tkn)) && is_redirection_token((*(ma->c_tkn))->type)) 
    {
        redir_node = create_ast_node(&(ma->first_node), NODE_REDIRECTION);
        redir_node->data.redirection.type = (*(ma->c_tkn))->type;
        get_next_token(ma);
        if (!is_word_token((*(ma->c_tkn))->type))
        {
            fprintf(stderr, "Error: Expected filename after redirection\n");
            exit(1);
        }
        redir_node->data.redirection.file = (*(ma->c_tkn))->value;
        get_next_token(ma);
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
        if (is_word_token((*(ma->c_tkn))->type))
            (*last_word)->data.word.next = parse_word_list(last_word, ma);
    }
    if (current)
        current->data.redirection.next = NULL;
    //printf("parse_redirection_list end\n");
    return (head);
}

/* 
 * Parses a simple cmd, which consists of a word list (cmd and its arguments)
 * and an optional list of redirections.
 * Returns a node representing the simple cmd.
 */
static t_astnode *parse_simple_cmd(t_ma *ma)
{
    t_astnode *node;
    t_astnode *last_word;
    
    //printf("parse_simple_cmd start\n");
    node = create_ast_node(&(ma->first_node), NODE_SIMPLE_CMD);
    node->data.simple_cmd.words = parse_word_list(&last_word, ma);
    node->data.simple_cmd.redirections = parse_redirection_list(&last_word, ma);
    //printf("parse_simple_cmd end\n");
    return (node);
}

/* 
 * Parses a cmd, which can be either a simple cmd or a cmd line
 * enclosed in parentheses.
 * Returns a node representing the cmd.
 */
static t_astnode *parse_cmd(t_ma *ma) 
{
    t_astnode *node;

    //printf("parse_cmd start\n");
    if ((*(ma->c_tkn))->type == TOKEN_LPAREN) 
    {
        get_next_token(ma);
        node = parse_cmd_line(ma);
        if ((*(ma->c_tkn)) && (*(ma->c_tkn))->type != TOKEN_RPAREN) 
        {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(1);
        }
        get_next_token(ma);
        //printf("parse_cmd end\n");
        return (node);
    } 
    else 
    {
        //printf("parse_cmd end\n");
        return parse_simple_cmd(ma);
    }
}

/* 
 * Parses a pipeline, which is a sequence of cmds connected by pipes (|).
 * Returns a node representing the pipeline.
 */
static t_astnode *parse_pipeline(t_ma *ma) 
{
    t_astnode *node;
    
    //printf("parse_pipeline start\n");
    node = create_ast_node(&(ma->first_node), NODE_PIPELINE);
    node->data.pipeline.cmds = g_c(&(ma->first_node), sizeof(t_astnode*))->data;
    node->data.pipeline.cmds[0] = parse_cmd(ma);
    node->data.pipeline.cmd_count = 1;
    
    while (((*(ma->c_tkn))) && (*(ma->c_tkn))->type == TOKEN_PIPE) 
    {
        get_next_token(ma);
        node->data.pipeline.cmd_count++;
        node->data.pipeline.cmds = ft_realloc_g_c(&(ma->first_node),\
                                        node->data.pipeline.cmds,\
                                        node->data.pipeline.cmd_count\
                                        * sizeof(t_astnode*));
        node->data.pipeline.cmds[node->data.pipeline.cmd_count - 1]\
                                = parse_cmd(ma);
    }
    //printf("parse_pipeline end\n");
    return (node);
}

/* 
 * Parses a cmd line, which can be a single pipeline or multiple pipelines
 * connected by AND (&&) or OR (||) operators.
 * Returns the root node of the parsed cmd line.
 */
t_astnode *parse_cmd_line(t_ma *ma) 
{
    t_astnode *node;
    t_astnode *new_node;
    
    //printf("parse_cmd_line start\n");
    node = parse_pipeline(ma);
    while ((*(ma->c_tkn)) &&((*(ma->c_tkn))->type == TOKEN_AND || (*(ma->c_tkn))->type == TOKEN_OR))
    {
        new_node = create_ast_node(&(ma->first_node), NODE_CMD_LINE);
        new_node->data.cmd_line.left = node;
        new_node->data.cmd_line.operator = (*(ma->c_tkn))->type;
        get_next_token(ma);
        new_node->data.cmd_line.right = parse_pipeline(ma);
        node = new_node;
    }
    //printf("parse_cmd_line end\n");
    return (node);
}