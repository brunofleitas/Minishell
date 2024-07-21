

#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_printf.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
  t_token_type: An enumeration representing different types of tokens encountered
  in a minishell environment.
  Values:
	TOKEN_COMMAND_ECHO: Represents an echo command token.
	TOKEN_COMMAND_CD: Represents a change directory command token.
	TOKEN_COMMAND_PWD: Represents a print working directory command token.
	TOKEN_COMMAND_EXPORT: Represents an export command token.
	TOKEN_COMMAND_UNSET: Represents an unset command token.
	TOKEN_COMMAND_ENV: Represents an environment variable command token.
	TOKEN_REDIR_IN: Represents an input redirection token.
	TOKEN_REDIR_OUT: Represents an output redirection token.
	TOKEN_REDIR_APPEND: Represents an append redirection token.
	TOKEN_HEREDOC: Represents a here document token.
	TOKEN_PIPE: Represents a pipe token.
	TOKEN_AND: Represents an AND logical operator token.
	TOKEN_OR: Represents an OR logical operator token.
	TOKEN_ENV_VAR: Represents a variable token.
	TOKEN_EXIT_STATUS: Represents a variable exit status token.
	TOKEN_SINGLE_QUOTE: Represents a single-quoted string token.
	TOKEN_DOUBLE_QUOTE: Represents a double-quoted string token.
	TOKEN_ARGUMENT: Represents a general argument token.
	TOKEN_ERROR: Represents an error token.
*/
/*
typedef enum e_token_type
{
	TOKEN_ERROR ,
	TOKEN_COMMAND_ECHO,
	TOKEN_COMMAND_CD,
	TOKEN_COMMAND_PWD,
	TOKEN_COMMAND_EXPORT,
	TOKEN_COMMAND_UNSET,
	TOKEN_COMMAND_ENV,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_ARGUMENT,
}				t_token_type;
*/

typedef enum    e_builtins
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
}				t_builtins;

typedef enum e_token_type
{
    TOKEN_WORD,           // Regular words/commands
    TOKEN_SINGLE_QUOTE,   // '
    TOKEN_DOUBLE_QUOTE,   // "
    TOKEN_REDIR_IN,       // <
    TOKEN_REDIR_OUT,      // >
    TOKEN_REDIR_APPEND,   // >>
    TOKEN_HEREDOC,        // <<
    TOKEN_PIPE,           // |
    TOKEN_ENV_VAR,        // $...
    TOKEN_EXIT_STATUS,    // $?
    TOKEN_AND,            // &&
    TOKEN_OR,             // ||
    TOKEN_LPAREN,         // (
    TOKEN_RPAREN,         // )
    TOKEN_WILDCARD,       // *
    TOKEN_EOF,            // End of input
    TOKEN_ARGUMENT,       // Is there an input? maybe this one we delete at some point let's see
    TOKEN_ERROR           // Error
} 			t_token_type;

/* ************************************************************************** */
/*                           STRUCTURE DEFINITIONS                            */                           
/* ************************************************************************** */
typedef struct  s_token
{
	t_token_type	type;
	char		    *value;
}				t_token;


/* ************************************************************************** */
/*                                  AST NODE                                  */                           
/* ************************************************************************** */

typedef enum e_nodetype 
{
    NODE_COMMAND_LINE,
    NODE_PIPELINE,
    NODE_COMMAND,
    NODE_SIMPLE_COMMAND,
    NODE_WORD,
    NODE_REDIRECTION
}			t_nodetype;

typedef struct s_astnode t_astnode;
struct s_astnode 
{
    t_nodetype type;
    t_nodetype *next;
    union {
        struct {
            t_astnode *left;
            t_astnode *right;
            int operator;
        } command_line;

        struct {
            t_astnode **commands;
            int command_count;
        } pipeline;
		
        struct {
            t_astnode *words;
            t_astnode *redirections;
			int word_count;
            int redirection_count;
        } simple_command;

        struct {
            char *value;
            int type;
        } word;

        struct {
            int type;
            char *file;
        } redirection;
    } data;
};

/*
Structs in the Union: Each struct within the union represents different types of node-specific data:

- command_line: For command line nodes, it contains pointers to left and right nodes and an operator (AND/OR).

- pipeline: For pipeline nodes, it contains an array of commands and the count of these commands.

- simple_command: For simple command nodes, it contains arrays of words and redirections, and their respective counts.

- word: For word nodes, it contains a string value and a type indicating what kind of word it is.

- redirection: For redirection nodes, it contains a type of redirection and a file name.

*/

/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */
void				lexer(char *input, t_ntc **first_node);
int					count_w_tks(char const *s, char c);
char				**ft_split_tokens(char const *s, char c, \
															t_ntc **first_node);
t_token_type		clasify_token(char *value);

t_astnode           *create_ast_node(t_ntc **first_node, t_nodetype type);
t_astnode           *parse_command_line(t_ntc **first_node);
t_astnode           *parse_pipeline(t_ntc **first_node);
t_astnode           *parse_command(t_ntc **first_node);
t_astnode           *parse_simple_command(t_ntc **first_node);
t_astnode           *parse_word_list(t_ntc **first_node);
t_astnode           *parse_word(t_ntc **first_node);
t_astnode           *parse_redirection_list(t_ntc **first_node);
t_astnode           *parse_redirection(t_ntc **first_node);

#endif