

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
  t_token_type: An enumeration representing different types of tkns encountered
  in a minishell environment.
  Values:
	TOKEN_cmd_ECHO: Represents an echo cmd token.
	TOKEN_cmd_CD: Represents a change directory cmd token.
	TOKEN_cmd_PWD: Represents a print working directory cmd token.
	TOKEN_cmd_EXPORT: Represents an export cmd token.
	TOKEN_cmd_UNSET: Represents an unset cmd token.
	TOKEN_cmd_ENV: Represents an environment variable cmd token.
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
	TOKEN_cmd_ECHO,
	TOKEN_cmd_CD,
	TOKEN_cmd_PWD,
	TOKEN_cmd_EXPORT,
	TOKEN_cmd_UNSET,
	TOKEN_cmd_ENV,
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
    TOKEN_BUILTIN,           // Regular words/cmds
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
    NODE_CMD_LINE,
    NODE_PIPELINE,
    NODE_cmd,
    NODE_SIMPLE_CMD,
    NODE_WORD,
    NODE_REDIRECTION
}			t_nodetype;

typedef struct s_astnode t_astnode;
struct s_astnode 
{
    t_nodetype type;
    union 
	{
        struct 
		{
            t_astnode *left;
            t_astnode *right;
            int operator;
        } cmd_line;

        struct 
		{
            t_astnode **cmds;
            int cmd_count;
        } pipeline;

        struct
		{
            t_astnode *words;
            t_astnode *redirections;
            int word_count;
            int redirection_count;
        } simple_cmd;

        struct
		{
            char *value;
            int type;
            t_astnode *next; // Linked list for words
        } word;

        struct
		{
            int type;
            char *file;
            t_astnode *next; // Linked list for redirections
        } redirection;
    } data;
};

/*
Structs in the Union: Each struct within the union represents different types of node-specific data:

- cmd_line: For cmd line nodes, it contains pointers to left and right nodes and an operator (AND/OR).

- pipeline: For pipeline nodes, it contains an array of cmds and the count of these cmds.

- simple_cmd: For simple cmd nodes, it contains arrays of words and redirections, and their respective counts.

- word: For word nodes, it contains a string value and a type indicating what kind of word it is.

- redirection: For redirection nodes, it contains a type of redirection and a file name.

*/

/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */
void	            lexer(char *input,t_token **tkns, t_ntc **first_node);
int					count_w_tks(char const *s, char c);
char				**ft_split_tkns(char const *s, char c, \
															t_ntc **first_node);
t_token_type		clasify_token(char *value);
t_token             *get_next_token(t_token **tkns);
t_astnode           *parser(t_ntc **first_node, t_token **tkns); 
t_astnode           *create_ast_node(t_ntc **first_node, t_nodetype type);
t_astnode           *parse_cmd_line(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_pipeline(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_simple_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_word_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_redirection_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
int                 is_word_token(t_token_type type);
int                 is_redirection_token(t_token_type type);  
#endif