/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12-AST_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bruno <bruno@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 13:08:01 by bfleitas          #+#    #+#             */
/*   Updated: 2024/08/27 17:14:19 by bruno            ###   ########.fr       */
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


static void add_word(t_astnode **first_word_node, t_astnode **current, t_astnode *word_node)
{
    if (!(*first_word_node))
    {
        *first_word_node = word_node;
        *current = *first_word_node;
    }
    else
    {
       (*current)->data.word.next = word_node;
       *current = word_node;
    }
}

/* 
 * Parses a list of words (cmd and its arguments).
 * Returns the head of a linked list of word nodes.
 */
static void parse_word_list(t_astnode *node, t_astnode **last_word, t_ma *ma) 
{
    t_astnode *current;
    t_astnode *word_node;

    if (*last_word)
        current = *last_word;
    else
        current = NULL;
    while ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type)) 
    {
        word_node = create_ast_node(&(ma->first_node), NODE_WORD);
        word_node->data.word.value = (*(ma->c_tkn))->value; 
        word_node->data.word.type = (*(ma->c_tkn))->type;
        word_node->data.word.next = NULL;
        add_word(&(node->data.simple_cmd.words), &(current), word_node);
        get_next_token(ma);
    }
    if (current)
        *last_word = current;
}



static void add_redir(t_astnode **first_redir_node, t_astnode **current, t_astnode *redir_node)
{
    if (!(*first_redir_node))
    {
        *first_redir_node = redir_node;
        *current = *first_redir_node;
    }
    else
    {
       (*current)->data.redirection.next = redir_node;
       *current = redir_node;
    }
}

static void parse_redirection_list(t_astnode *node, t_astnode **last_word, t_ma *ma)
{

    t_astnode *current;
    t_astnode *redir_node;
    
    current = NULL;
    while ((*(ma->c_tkn)) && is_redirection_token((*(ma->c_tkn))->type)) 
    {
        redir_node = create_ast_node(&(ma->first_node), NODE_REDIRECTION);
        redir_node->data.redirection.type = (*(ma->c_tkn))->type;
        get_next_token(ma);
        if ((*(ma->c_tkn)) && !is_word_token((*(ma->c_tkn))->type))
        {
            fprintf(stderr, "Error: Expected filename after redirection\n");
            exit(1);
        }
        redir_node->data.redirection.file = (*(ma->c_tkn))->value;
        redir_node->data.redirection.next = NULL;
        get_next_token(ma);
        add_redir(&(node->data.simple_cmd.redirections), &(current), redir_node);
        // ft_printf("redir_node->data.simple_cmd.redirections_in : %p\n" ,node->data.simple_cmd.redirections_in);
        // ft_printf("redir_node->data.simple_cmd.redirections_out : %p\n" ,node->data.simple_cmd.redirections_out);
        if ((*(ma->c_tkn)) && is_word_token((*(ma->c_tkn))->type))
            parse_word_list(node, last_word, ma);
    }
}

/* 
 * Parses a simple cmd, which consists of a word list (cmd and its arguments)
 * and an optional list of redirections.
 * Returns a node representing the simple cmd.
 */
static t_astnode *parse_simple_cmd(t_ma *ma)
{
    t_astnode   *node;
    t_astnode   *last_word;
    // t_astnode   *current;
    // int         i=0;
    // int         j=0;
    // int         k=0;
    // ft_printf("parse_simple_cmd start\n");
    last_word = NULL;
    node = create_ast_node(&(ma->first_node), NODE_SIMPLE_CMD);
    node->data.simple_cmd.words = NULL;
    node->data.simple_cmd.redirections = NULL;
    parse_word_list(node, &last_word, ma);
    parse_redirection_list(node, &last_word, ma);
    // ft_printf("node->data.simple_cmd.redirection_in : %p\n" ,node->data.simple_cmd.redirections_in);
    // ft_printf("node->data.simple_cmd.redirection_out : %p\n" ,node->data.simple_cmd.redirections_out);
    // ft_printf("node->data.simple_cmd.words : %p\n" ,node->data.simple_cmd.words);
    // current = node->data.simple_cmd.words;
    // while (current)
    // {
    //     ft_printf("word %i, %s\n", k++, current->data.word.value);
    //     current = current->data.word.next;
    // }
    // current = node->data.simple_cmd.redirections_in;
    // while (current)
    // {
    //     ft_printf("redir_in %i, file name: %s\n", i++, current->data.redirection.file);
    //     current = current->data.redirection.next;
    // }
    // current = node->data.simple_cmd.redirections_out;
    // while (current)
    // {
    //     ft_printf("redir_out %i, file name: %s\n", j++, current->data.redirection.file);
    //     current = current->data.redirection.next;
    // }
    // ft_printf("node->data.simple_cmd.redirection_in : %p\n" ,node->data.simple_cmd.redirections_in);
    // printf("parse_simple_cmd end\n");
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