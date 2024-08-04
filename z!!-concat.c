#include "ft_printf.h"
#include "libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>


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

typedef struct s_env
{
	char					**var;
	int						count;
    int                     capacity;  // Current capacity of the var array. I propose to add this to the struct in order to keep track of the current capacity of the var array. Here what I call capacity is the number of elements that the var array can hold at the moment. This is useful when we want to add a new element to the array. If the array is full, we can reallocate memory to increase the capacity of the array. This avoid calling ft_realloc_g_c for each new variable. We call it only when count == capacity.
}							t_env;

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
/*                                   AST EXECUTION                            */
/* ************************************************************************** */

/* ***************************  EXECUTE_PIPELINE_ARGS  ********************** */

typedef struct  s_pipeline_args
{
    int     pipe_fds[2];
    int     input_fd;
    pid_t   pid;
    pid_t   last_pid;
    int     status;
    int     last_cmd;
}               t_pip_args;

/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */
t_env               duplicate_vars(t_ntc **first_node, char **envp);
void                print_env(t_env env);

void	            lexer(char *input,t_token **tkns, t_ntc **first_node);
int					count_w_tks(char const *s, char c);
char				**ft_split_tkns(char const *s, char c, \
															t_ntc **first_node);
t_token_type		clasify_token(char *value);
t_token             *get_next_token(t_token **tkns, int t);
t_astnode           *parser(t_ntc **first_node, t_token **tkns); 
t_astnode           *create_ast_node(t_ntc **first_node, t_nodetype type);
t_astnode           *parse_cmd_line(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_pipeline(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_simple_cmd(t_ntc **first_node, t_token *c_tkn, t_token **tkns);
t_astnode           *parse_word_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns, t_astnode **last_word);
t_astnode           *parse_redirection_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns, t_astnode **last_word);
int                 is_word_token(t_token_type type);
int                 is_redirection_token(t_token_type type);
char                *execute_command(t_astnode *node, t_ntc **first_node, char **env);
int                builtin_export(t_astnode *node, t_env *env, t_ntc **first_node);
int                 execute_pipeline(t_ntc **first_node, t_astnode *node, t_env *env);




int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char		*input;
	t_ntc		*first_node;
	t_token		*tkns[1024];
	t_env		env;
	//t_astnode	*root;

	first_node = NULL;
	while (1)
	{
		input = readline(">>");
		if (input)
		{
			if (ft_strcmp(input, "exit") == 0)
			{
				free(input);
				break ;
			}
			env = duplicate_vars(&first_node, envp);
			print_env(env);
			add_history(input);
			lexer(input, tkns, &first_node);
			parser(&first_node, tkns);
			//root = parse_cmd_line(&first_node, tkns);
			//free_ast(&root);
			free(input);
		}
		else
			break ;
	}
	clear_history();
	free_memory(&first_node);
	return (0);
}



static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

static char	**allocate_env(t_ntc **first_node, int count)
{
	char	**new_envp;

	new_envp = g_c(first_node, (count + 1) * sizeof(char *))->data;
	if (!new_envp)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_envp);
}

static void	free_env_vars(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->count)
	{
		free(env->var[i]);
		i++;
	}
	free(env->var);
}

t_env	duplicate_vars(t_ntc **first_node, char **envp)
{
	t_env	env;
	int		i;

	env.count = count_env_vars(envp);
	env.var = allocate_env(first_node, env.count);
	if (!env.var)
		return (env);
	i = 0;
	while (i < env.count)
	{
		env.var[i] = ft_strdup_g_c(envp[i], first_node);
		if (!env.var[i])
		{
			perror("ft_strdup_g_c");
			free_env_vars(&env);
		}
		i++;
	}
	env.var[env.count] = NULL;
	return (env);
}

void	print_env(t_env env)
{
	int i;

	i = 0;
	while (env.var[i])
	{
		printf("%s\n", env.var[i]);
		i++;
	}
}

void	lexer(char *input,t_token **tkns, t_ntc **first_node)
{
	char	**split;
	int		i;

	i = 0;
	split = ft_split_tkns(input, ' ', first_node);
	while (split[i])
	{
		tkns[i] = g_c(first_node, sizeof(t_token))->data;
		tkns[i]->value = split[i];
		tkns[i]->type = clasify_token(tkns[i]->value);
		ft_printf("%s\nType : %i\n\n", tkns[i]->value, tkns[i]->type);
		//free_ntc_prior(first_node, split[i]);
		i++;
	}
	free_ntc_prior(first_node, split);
	//free(split);
}

int	count_w_tks(char const *s, char c)
{
	int	counter;
	int	i;

	counter = 0; 
	i = 0;
	if (*s == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			counter += handle_quotes(s, &i);
		else if (handle_double_operators(s, &i)
			|| handle_single_operators_and_specials(s, &i))
			counter++;
		else if (s[i] != c && (i == 0 || s[i - 1] == c))
			counter++;
		i++;
	}
	return (counter);
}
static void	generate_quotes(const char **s, char ***split, int *i, t_ntc **first_node)
{
	char	quote;
	int		word_length;

	quote = **s;
	(*s)++;
	word_length = 0;
	while ((*s)[word_length] != quote && (*s)[word_length])
		word_length++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, word_length, first_node);
	if ((*s)[word_length] != '\0')
		*s += word_length + 1;
	else
		*s += word_length;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a double operator (e.g., '>>', '<<', '&&', '||') from 
	the input string into the tkns array. Advances the input string by 2 
	positions to skip the operator.
*/
static void	generate_double_operators(const char **s, char ***split, int *i, \
															t_ntc **first_node)
{
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, 2, first_node);
	*s += 2;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a single operator or special character (including '$?') 
	from the input string into the tkns array. The length of the substring 
	depends on the specific operator or special character.
    Advances the input string by the length of the extracted substring.
*/
static void	generate_single_operators_and_specials(const char **s,
		char ***split, int *i, t_ntc **first_node)
{
	int	len;

	len = 1;
	if (**s == '$' && *(*s + 1) == '?')
		len = 2;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, len, first_node);
	*s += len;
}

/*
  Parameters:
    s: Pointer to the input string.
    split: Pointer to the array of pointers to strings (tkns).
    i: Pointer to an integer indicating the current index in the tkns array.
  Description:
    Extracts and stores a regular token (any sequence of characters not 
	matching the specified operators or special characters) from the input 
	string into the tkns array. Calculates the length of the token by finding 
	the first occurrence of an operator or special character. Advances the 
	input string by the length of the extracted token.
*/
static void	generate_regular_tkns(const char **s, char ***split, int *i, \
																t_ntc **first_node)
{
	int	word_length;

	word_length = 0;
	while ((*s)[word_length] && !strchr(" ><&()|$", (*s)[word_length]))
		word_length++;
	(*split)[(*i)++] = ft_substr_g_c(*s, 0, word_length, first_node);
	*s += word_length;
}

/*
  Parameters:
	s: Input string to be split into tkns.
	c: Character used to determine token boundaries.
  Return value:
	A pointer to an array of strings, each representing a token from the input
	string.
	Returns NULL if the input string or the allocated memory cannot be processed
  Description:
	Splits the input string into tkns based on the specified delimiter
	character.
	Handles various cases including quotes, double operators, single operators,
	and regular tkns. Allocates memory for the resulting array of tkns and
	initializes it accordingly. The last element of the array is set to NULL
	to indicate the end.
*/
char	**ft_split_tkns(char const *s, char c, t_ntc **first_node)
{
	char	**split;
	int		i;

	i = 0;
	split = g_c(first_node, (count_w_tks(s, c) + 1) * sizeof(char *))->data;
	if (!s || !split)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*s == '"' || *s == '\'')
			generate_quotes(&s, &split, &i, first_node);
		else if ((*s == '>' && *(s + 1) == '>') || (*s == '<' && *(s
					+ 1) == '<') || (*s == '&' && *(s + 1) == '&') || (*s == '|'
				&& *(s + 1) == '|'))
			generate_double_operators(&s, &split, &i, first_node);
		else if (*s == '>' || *s == '<' || *s == '(' || *s == ')' || *s == '|'
			|| (*s == '$' && *(s + 1) == '?') || *s == '$')
			generate_single_operators_and_specials(&s, &split, &i, first_node);
		else
			generate_regular_tkns(&s, &split, &i, first_node);
	}
	split[i] = NULL;
	return (split);
}

static t_token_type	classify_cmd(char *value)
{
	if (ft_strcmp(value, "echo") == 0 
	|| ft_strcmp(value, "cd") == 0 || ft_strcmp(value, "pwd") == 0\
	|| ft_strcmp(value, "export") == 0 || ft_strcmp(value, "unset") == 0\
	|| ft_strcmp(value, "env") == 0)
		return (TOKEN_BUILTIN);
	return (TOKEN_ERROR);
}

static t_token_type	classify_operator(char *value)
{
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "&&") == 0)
		return (TOKEN_AND);
	if (ft_strcmp(value, "||") == 0)
		return (TOKEN_OR);
	return (TOKEN_ERROR);
}

static t_token_type	classify_variable(char *value)
{
	if (value[0] == '$' && value[1] == '?')
		return (TOKEN_EXIT_STATUS);
	if (value[0] == '$')
		return (TOKEN_ENV_VAR);
	return (TOKEN_ERROR);
}

static t_token_type	classify_string(char *value)
{
	if (value[0] == '\'' && value[ft_strlen(value) - 1] == '\'')
		return (TOKEN_SINGLE_QUOTE);
	if (value[0] == '"' && value[ft_strlen(value) - 1] == '"')
		return (TOKEN_DOUBLE_QUOTE);
	return (TOKEN_ERROR);
}

t_token_type	clasify_token(char *value)
{
	int	token_type;

	token_type = classify_cmd(value);
	if (token_type != TOKEN_ERROR)
		return (TOKEN_BUILTIN);
	token_type = classify_operator(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_variable(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	token_type = classify_string(value);
	if (token_type != TOKEN_ERROR)
		return (token_type);
	if (ft_strlen(value) > 0)
		return (TOKEN_WORD);
	return (TOKEN_ERROR);
}


t_astnode *parser(t_ntc **first_node, t_token **tkns) 
{
    t_token     *c_tkn;
    t_astnode   *cmd_line;
    /*t_astnode   *pipeline;
    t_astnode   *simple_cmd;
    t_astnode   *current;*/

    c_tkn = get_next_token(tkns, 1); // Initialize c_tkn
    cmd_line = parse_cmd_line(first_node, c_tkn, tkns);
    print_ast(cmd_line, 0);
    // Print the parsed words in the first simple cmd
    /*if (cmd_line->type == NODE_CMD_LINE) 
    {
        pipeline = cmd_line->data.cmd_line.left;
        if (pipeline->type == NODE_PIPELINE) 
        {
            simple_cmd = pipeline->data.pipeline.cmds[0];
            current = simple_cmd->data.simple_cmd.words;
            while (current) 
            {
                printf("Word: %s\n", current->data.word.value);
                current = current->data.word.next;
            }*
        }
    } 
    else if (cmd_line->type == NODE_PIPELINE) 
    {
        simple_cmd = cmd_line->data.pipeline.cmds[0];
        current = simple_cmd->data.simple_cmd.words;
        while (current) 
        {
            printf("Word: %s\n", current->data.word.value);
            current = current->data.word.next;
        }
    }
    else 
    {
        // Handle unexpected type (for robustness)
        fprintf(stderr, "Error: Unexpected node type\n");
    }
    */
    return cmd_line;
}

t_astnode *create_ast_node(t_ntc **first_node, t_nodetype type) 
{
    t_astnode *node;
    
    node = g_c(first_node, sizeof(t_astnode))->data;
    if (!node)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    node->type = type;
    return (node);
}

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
        c_tkn = get_next_token(tkns, 1);
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
        c_tkn = get_next_token(tkns, 1);
        node = parse_cmd_line(first_node, c_tkn, tkns);
        if (c_tkn->type != TOKEN_RPAREN) 
        {
            fprintf(stderr, "Error: Expected closing parenthesis\n");
            exit(1);
        }
        c_tkn = get_next_token(tkns, 1);
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
    t_astnode *last_word;
    
    node = create_ast_node(first_node, NODE_SIMPLE_CMD);
    node->data.simple_cmd.words = parse_word_list(first_node, c_tkn, tkns, &last_word);
    node->data.simple_cmd.redirections = parse_redirection_list(first_node, c_tkn, tkns, &last_word);
    return (node);
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
    while (is_word_token(c_tkn->type)) 
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
    *last_word = current;
    current->data.word.next = NULL;
    return (head);
}

/* 
 * Parses a list of redirections.
 * Returns the head of a linked list of redirection nodes.
 */
t_astnode *parse_redirection_list(t_ntc **first_node, t_token *c_tkn, t_token **tkns, t_astnode **last_word) 
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
    current->data.redirection.next = NULL;
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


t_token *get_next_token(t_token **tkns, int t) 
{
    static int i;

    if (!tkns[i])
        return (NULL);
    return (tkns[i++]);
}

static void change_directory(char *path, t_env *env, t_ntc *first_node)
{
	char	cwd[PATH_MAX];
	char	*new_pwd;
    size_t  len;

	if (chdir(path) == -1)
		perror("errpr chdir");
	if (!getcwd(cwd, sizeof(cwd)))
		perror("getcwd");
    len = 4 + ft_strlen(cwd) + 1;
	new_pwd = g_c(first_node, (4 + ft_strlen(cwd) + 1));
	if (!new_pwd)
		perror("malloc");
	ft_strlcpy(new_pwd, "PWD=", len);
	ft_strlcat(new_pwd, cwd, len);
	export_var(env, new_pwd);
	free(new_pwd);
}

/*
  Parameters:
    node: Pointer to the AST node.
    first_node: Pointer to the first t_ntc node.
    env: Pointer to the environment variables.
  Return value:
    None.
  Description:
    Handles the "cd" built-in command. Changes the directory to the 
    specified path. If no path is provided, changes to the home directory. 
    Handles errors for too many arguments and invalid paths.
*/
void	builtin_cd(t_astnode *node, t_ntc *first_node, t_env *env)
{
    t_astnode    *path;

    path = node->data.simple_cmd.words->data.word.next;
    if (!path->data.word.value)
    {
        path = get_env_var("HOME", env);
        change_directory(path , env, first_node);
    }
    else if(path->data.word.next)
        perror("cd: too many arguments");
    else //check if path is valid
        change_directory(path->data.word.value, env, first_node);
}

void	builtin_export(t_astnode *node, t_env *env, t_ntc **first_node)
{
	t_astnode	*tmp;
  int       i;
	char      *var;

	tmp = node->data.simple_cmd.words;
	var = tmp->data.word.next->data.word.value;
	i = find_env_var(env, var);
	if (i)
		update_env_var(env, i, var, first_node);
	else
		add_env_var(env, var, first_node);
}

static int	unset_var(t_env *env, const char *name)
{
	int	i;

	i = find_env_var(env, name);
	if (i == 0)
		return (0);
	free(env->var[i]);
	while (i < env->count - 1)
	{
		env->var[i] = env->var[i + 1];
		i++;
	}
	env->var[env->count - 1] = NULL;
	env->count = env->count - 1;
	return (0);
}

*/
char	*builtin_echo(t_astnode *node, t_ntc **first_node)
{
	int		newline;
	int		i;
	char	*result;
	char	*temp;

	newline = should_add_newline(node);
	if (newline)
		i = 1;
	else
		i = 2;
	result = join_words(node, first_node, i);
	if (newline)
	{
		temp = ft_strjoin(result, "\n", first_node);
		free(result);
		result = temp;
	}
	return (result);
}

char	*builtin_pwd(t_ntc **first_node)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		return (ft_strdup_g_c(cwd, first_node));
	else
		ft_printf("getcwd() error");
	return (NULL);
}

char	*builtin_env(char **env, t_ntc **first_node)
{
	int		i;
	size_t	total_length;
	char	*result;
	char	*temp;

	i = 0;
	total_length = 0;
	while (env[i] != NULL)
	{
		total_length += ft_strlen(env[i]) + 1;
		i++;
	}
	result = g_c(first_node, (total_length + 1) * sizeof(char *))->data;
	if (!result)
		return (NULL);
	i = 0;
	while (env[i] != NULL)
	{
		ft_strlcat(result, env[i], total_length + 1);
		ft_strlcat(result, "\n", total_length + 1);
		i++;
	}
	return (result);
}

/*
  Parameters:
    output: String to write to the file.
    file_name: Name of the file to write to.
  Return value:
    None.
  Description:
    Opens the specified file for writing, creating it if it doesn't
    exist, and truncating it if it does. Writes the output string 
    to the file. Handles errors for opening and writing to the file.
*/
void	redirect_output(const char *output, const char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

/*
  Parameters:
    output: String to append to the file.
    file_name: Name of the file to append to.
  Return value:
    None.
  Description:
    Opens the specified file for appending, creating it if it doesn't
    exist. Appends the output string to the file. Handles errors for 
    opening and writing to the file.
*/
void	redirect_output_append(const char *output, const char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_printf("open() error");
		return ;
	}
	if (write(fd, output, ft_strlen(output)) == -1)
		ft_printf("write() error");
	close(fd);
}

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

#include "minishell.h"

static void setup_pipe(int pipe_fds[2])
{
    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        exit(1);
    }
}

static pid_t    fork_process()
{
    pid_t pid;
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    return (pid);
}

static void child_process(t_ntc **first_node, t_pip_args *a, t_astnode *simple_cmd, t_env *env)
{
    if (a->input_fd != STDIN_FILENO)
    {
        dup2(a->input_fd, STDIN_FILENO);
        close(a->input_fd);
    }
    if (!a->last_cmd)
    {
        dup2(a->pipe_fds[1], STDOUT_FILENO);
        close(a->pipe_fds[0]);
        close(a->pipe_fds[1]);
    }
    exit(execute_ast(simple_cmd, env, first_node));
}

static void parent_process(t_pip_args *a)
{
    if (a->input_fd != STDIN_FILENO)
        close(a->input_fd);
    if (!(a->last_cmd))
    {
        close(a->pipe_fds[1]);
        a->input_fd = a->pipe_fds[0];
    }
    a->last_pid = a->pid;
}

int execute_pipeline(t_astnode *node, t_env *env, t_ntc **first_node)
{
    t_pip_args  a;
    int         i;
    
    i = 0;
    a.input_fd = STDIN_FILENO;
    while (i < node->data.pipeline.cmd_count)
    {
        a.last_cmd = (i == node->data.pipeline.cmd_count - 1);
        if (!node->data.pipeline.cmd_count - 1)
            setup_pipe(a.pipe_fds);
        a.pid = fork_process();
        if (a.pid == 0)
            child_process(&a, node->data.pipeline.cmds[i], env, first_node);
        else
            parent_process(&a);
        i++;
    }
    waitpid(a.last_pid, &(a.status), 0);
    return (WEXITSTATUS(a.status));
}

int is_builtin(const char *word)
{
    const char *builtins[7];
    int i = 0;

    i=0;
    builtins[0] = "echo";
    builtins[1] = "cd";
    builtins[2] = "pwd";
    builtins[3] = "export";
    builtins[4] = "unset";
    builtins[5] = "env";
    builtins[6] = NULL;
    while (builtins[i])
    {
        if (ft_strcmp(word, builtins[i]) == 0)
            return (1);
        i++;
    }
    return (0);
}

/**
 * @brief Execute a builtin command
 *
 * This function executes the appropriate builtin command based on the
 * command name. It handles echo, cd, pwd, export, unset, and env commands.
 *
 * @param args Array of command arguments
 * @param env Pointer to the environment structure
 * @return int Returns the exit status of the builtin command
 */
int execute_builtin(char **args, t_env *env, t_ntc **first_node)
{
    if (ft_strcmp(args[0], "echo") == 0)
        return (builtin_echo(args));
    else if (ft_strcmp(args[0], "cd") == 0)
        return (builtin_cd(args, env));
    else if (ft_strcmp(args[0], "pwd") == 0)
        return (builtin_pwd());
    else if (ft_strcmp(args[0], "export") == 0)
        return (builtin_export(args, env, first_node));
    else if (ft_strcmp(args[0], "unset") == 0)
        return (builtin_unset(args, env));
    else if (ft_strcmp(args[0], "env") == 0)
        return (builtin_env(env));
    return 1;
}