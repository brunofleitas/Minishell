#ifndef MINISHELL_H
# define MINISHELL_H

#include "./libft/headers/libft.h"
#include "./libft/headers/ft_printf.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h> //added to handle wildcards
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>


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
    TOKEN_REDIR_OUT_NUM,  // n>
    TOKEN_REDIR_APPEND,   // >>
    TOKEN_REDIR_APPEND_NUM, // n>>
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
    TOKEN_WORD,       // Is there an input? maybe this one we delete at some point let's see
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
/*
typedef struct s_main_args
{
    char    *input;
    t_ntc   *first_node;
    t_ntc   *first_env;
    t_token *tkns[1024];
    t_env   *env;
    t_astnode *node;
}               t_ma;
*/
typedef struct s_env
{
	char					**var;
	int						count;
    int                     capacity;  
}							t_env;
// Current capacity of the var array. I propose to add this to the struct in order to keep track of the current capacity of the var array. Here what I call capacity is the number of elements that the var array can hold at the moment. This is useful when we want to add a new element to the array. If the array is full, we can reallocate memory to increase the capacity of the array. This avoid calling ft_realloc_g_c for each new variable. We call it only when count == capacity.
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
            int  fd_num; //added to handle cases like 2>output
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

typedef struct  s_main_args
{
    char        *input;
	t_ntc		*first_node;
    t_ntc		*first_env;
	t_token		*tkns[1024];
    t_token     **c_tkn;
	t_env		*env;
    int         tmp_file_counter;// added for creation of temporary files in heredoc
    int         last_exit_status;
}               t_ma;

/* ************************************************************************** */
/*                                   AST EXECUTION                            */
/* ************************************************************************** */

/* ***************************  EXECUTE_PIPELINE_ARGS  ********************** */

typedef struct  s_pipeline_args
{
    int     pipe_fds[2];
    int     input_fd;
    pid_t   pid;
    pid_t   *pid_arr;
    // pid_t   last_pid;
    int     status;
    int     last_cmd;
}               t_pip_args;

/* *************************  EXECUTE_SIMPLE_CMD_ARGS  ********************* */

typedef struct  s_simple_cmd_args
{
    int     word_count;
    int     status;
    char    **words_arr;
    int     saved_stdin;
    int     saved_stdout;
}               t_s_cmd_args;

/* *************************  EXPAND_WILDCARDS_ARGS  ********************* */

typedef struct s_expand_wildcards_args
{
    char    **exp_args;
    int     count;
    int     capacity;
}               t_wc_args;

/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */
t_env           *duplicate_vars(t_ntc **first_node, char **envp);
void            lexer(t_ma *ma);
int             count_tks(char const *s, char c);
char            **ft_split_tkns(char c, t_ma *ma);
t_token_type    clasify_token(char *value);
t_astnode       *parser(t_ma *ma);
t_astnode       *create_ast_node(t_ntc **first_node, t_nodetype type);
t_astnode       *parse_cmd_line(t_ma *ma);
void            get_next_token(t_ma *ma);
int             execute_builtin(char **args, t_ma *ma);
int             is_builtin(const char *word);
int             execute_cmd_line(t_astnode *node, t_ma *ma);
int             execute_pipeline(t_astnode *node, t_ma *ma);
int             execute_simple_cmd(t_astnode *node, t_ma *ma);
int             execute_external_cmd(char **words_arr, t_env **env, t_ntc **first_node);
int builtin_exit(t_ma *ma, char **args);
int             builtin_pwd(char **args, t_ma *ma);
int             builtin_echo(char **args, int count_words, t_ma *ma);
int             builtin_env(char **args, t_ma *ma);
int             builtin_export(char **args, t_ma *ma);
int             builtin_unset(char **args, t_ma *ma);
int             builtin_cd(char **args, t_ma *ma);
int             find_env_var(t_env **env, char *var);
int             execute_ast(t_astnode *node, t_ma *ma);
pid_t           fork_process();
int	            update_env_var(int i, const char *var, t_ma *ma);
int             handle_redirections(t_astnode *redir_node, t_ma *ma);
void	        print_env(t_env *env);
char            **expand_wildcards_in_args(char **args, t_ma *ma);
int	               expand_wildcard(t_wc_args *a, char *pattern, t_ma *ma);
int             add_single_element(t_wc_args *a, char *name, t_ma *ma);
int	            match_pattern(const char *str, const char *pattern);

#endif