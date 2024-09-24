/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:50:17 by bfleitas          #+#    #+#             */
/*   Updated: 2024/09/24 11:33:46 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/headers/ft_printf.h"
# include "./libft/headers/libft.h"
# include <ctype.h>
# include <dirent.h> //added to handle wildcards
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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
typedef enum e_builtins
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
}							t_builtins;

typedef enum e_token_type
{
	TOKEN_BUILTIN,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_HEREDOC,
	TOKEN_PIPE,
	TOKEN_ENV_VAR,
	TOKEN_EXIT_STATUS,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_WILDCARD,
	TOKEN_EOF,
	TOKEN_ARGUMENT,
	TOKEN_WORD,
	TOKEN_ERROR
}							t_token_type;

/* ************************************************************************** */
/*                           STRUCTURE DEFINITIONS                            */
/* ************************************************************************** */

typedef struct s_gnl_buffer
{
	char	*ptr;
	char	*start;
	size_t	len;
	size_t	cap;
}	t_gnl_buffer;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
}							t_token;

typedef struct s_env
{
	char					**var;
	int						count;
	int						capacity;
}							t_env;

typedef struct s_main_args
{
	char					*program;
	int						l_program;
	char					*input;
	t_ntc					*first_node;
	t_ntc					*first_env;
	t_token					*tkns[1024];
	t_token					**c_tkn;
	t_env					*env;
	int						tmp_file_counter;
	int						last_exit_status;
	int						in_child_p;
	int						saved_stdin;
	int						saved_stdout;
	int						saved_stderr;
	int						delimiter;
	int						and_or;
	int						heredoc_f;
}							t_ma;

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
}							t_nodetype;

typedef struct s_astnode	t_astnode;

struct						s_astnode
{
	t_nodetype				type;
	union
	{
		struct
		{
			t_astnode		*left;
			t_astnode		*right;
			int				operator;
		} s_cmd_line;
		struct
		{
			t_astnode		**cmds;
			int				cmd_count;
			t_astnode		**cmds_redir;
		} s_pipeline;
		struct
		{
			t_astnode		*words;
			t_astnode		*redirections;
			int				word_count;
		} s_simple_cmd;
		struct
		{
			char			*value;
			int				type;
			t_astnode		*next;
		} s_word;
		struct
		{
			int				type;
			char			*file;
			int				fd_num;
			t_astnode		*next;
		} s_redirection;
	} u_data;
};

/*
Structs in the Union: Each struct within the union represents different 
types of node-specific data:

- cmd_line: For cmd line nodes,
	it contains pointers to left and right nodes and an operator (AND/OR).

- pipeline: For pipeline nodes,
	it contains an array of cmds and the count of these cmds.

- simple_cmd: For simple cmd nodes,
	it contains arrays of words and redirections, and their respective counts.

- word: For word nodes,
	it contains a string value and a type indicating what kind of word it is.

- redirection: For redirection nodes,
	it contains a type of redirection and a file name.

*/

/* ************************************************************************** */
/*                                   AST EXECUTION                            */
/* ************************************************************************** */

/* ***************************  EXECUTE_PIPELINE_ARGS  ********************** */

typedef struct s_pipeline_args
{
	int						pipe_fds[2];
	int						input_fd;
	pid_t					pid;
	pid_t					*pid_arr;
	int						last_status;
	int						status;
	int						last_cmd;
}							t_pip_args;

/* *************************  EXECUTE_SIMPLE_CMD_ARGS  ********************* */

typedef struct s_simple_cmd_args
{
	int						word_count;
	int						status;
	char					**words_arr;
	int						i_c;
	//  in_critical is a flag that indicates if the command is critical or not. 
	//  If the command is critical, the shell should exit if the command fails. 
	//  If the command is not critical, the shell should continue executing 
	//  the next command.
	int						s_inredir;
	// successfull input redirection or heredoc
}							t_s_cmd_args;

/* *************************  EXPAND_WILDCARDS_ARGS  ********************* */

typedef struct s_expand_wildcards_args
{
	char					**exp_args;
	int						count;
	int						capacity;
	int						count_match;
	int						count_cpy;
}							t_wc_args;

/* ************************************************************************** */
/*                                   FUNCTIONS                                */
/* ************************************************************************** */

void					sigint_handler(int sig);
void					init_ma(t_ma *ma, char **argv, char **envp);
void					process_input(t_ma *ma, char ***delimiters_h,
							int *heredoc_f);
void					restore_io_fds(t_ma *ma, int *fix_stdin,
							int *fix_stdout, int *fix_stderr);

void					restore_io(t_ma *ma);

int						count_env_vars(char **envp);
char					**allocate_env(t_ntc **first_node, int count);
t_env					*duplicate_vars(t_ntc **first_node, char **envp);

char					*trim_wildcard(char *wildcard, t_ma *ma,
							t_token_type type);
void					process_wildcards(char **wildcards, t_ma *ma);
int						handle_ambiguous_redirect(char **split);
void					handle_single_wildcard(char **split, t_ma *ma);
void					lexer(t_ma *ma);

int						count_tks(char const *s, char c);

int						handle_quotes(const char *s, int *i);
int						handle_double_operators(const char *s, int *i);
int						handle_single_operators_and_specials(const char *s,
							int *i);
int						handle_special_cases(const char *s, int *i);
int						handle_token_increments(const char *s, int *i);

void					process_char(const char **s, char ***split, int *i,
							t_ma *ma);
char					**ft_split_tkns(char c, t_ma *ma);

void					generate_quotes(const char **s, char ***split,
							int *i, t_ma *ma);
void					append_char(char s, char **result, t_ma *ma);
void					handle_quote_content(const char **s, char **result,
							char quote, t_ma *ma);
void					handle_newline_if_needed(const char **s,
							char **result, t_ma *ma);

int						handle_special(const char **s, char **result,
							char quote, t_ma *ma);
int						handle_double_q(const char **s, char **result,
							char quote, t_ma *ma);
void					handle_env_var(const char **s, char **result,
							t_ma *ma);
char					*get_env(char *name, char **env, t_ma *ma);
char					*remove_extra_spaces(char *str, t_ma *ma);

void					generate_double_operators(const char **s,
							char ***split, int *i, t_ma *ma);

void					generate_single_operators_and_specials(const char **s,
							char ***split, int *i, t_ma *ma);
void					handle_env_vari(const char **s, char ***split,
							int *i, t_ma *ma);
void					handle_regular_substring(const char **s,
							char ***split, int *i, t_ma *ma);

void					generate_regular_tkns(const char **s, char ***split,
							int *i, t_ma *ma);
int						get_word_length(const char *s);
char					*handle_env_in_var(char *var, t_ma *ma);
char					*process_dollar_expansion(const char **s,
							char *temp, int word_length, t_ma *ma);
char					*ft_strremove_quotes(const char *str,
							t_ntc **first_node);

void					append_env_value(const char *temp, int *i,
							char **result, t_ma *ma);
char					*get_env_var_value(const char *s, int word_length,
							int len_var, t_ma *ma);
char					*append_remaining_word(const char *s,
							int word_length, int len_var, t_ma *ma);
void					handle_dq(const char *str, char *result, int *i,
							int *j);
void					handle_sq(const char *str, char *result, int *i,
							int *j);

char					**expand_wildcards_in_args(char **args, t_ma *ma);
int						expand_single_arg(t_wc_args *a, char *arg,
							t_ma *ma);

int						expand_wildcard(t_wc_args *a, char *pattern,
							t_ma *ma);
int						process_directory(t_wc_args *a, DIR *dir,
							char *pattern, t_ma *ma);
int						add_single_element(t_wc_args *a, char *name,
							t_ma *ma);

int						match_star_pattern(const char *str,
							const char *pattern);
int						is_pattern_end(const char *pattern);
int						match_pattern(const char *str, const char *pattern);

int						ft_strcmp2(char const *s1, char const *s2);
void					minishell_sort_str(char *tab[], size_t size);

t_token_type			clasify_cmd(char *value);
t_token_type			clasify_operator(char *value);
t_token_type			clasify_variable(char *value);
t_token_type			clasify_string(char *value);
t_token_type			clasify_token(char *value);

void					get_next_token(t_ma *ma);

t_astnode				*create_ast_node(t_ntc **first_node,
							t_nodetype type);

t_astnode				*parser(t_ma *ma);

void					check_cmd_line_syntax(t_ma *ma);
t_astnode				*create_cmd_line_node(t_astnode *node, t_ma *ma);
t_astnode				*parse_cmd_line(t_ma *ma);

void					store_cmd_redirections(t_astnode *node, t_ma *ma);
void					check_next_token(t_ma *ma);
void					add_command_to_pipeline(t_astnode *node, t_ma *ma);
t_astnode				*parse_pipeline(t_ma *ma);

t_astnode				*parse_cmd(t_ma *ma);

t_astnode				*parse_simple_cmd(t_ma *ma);

int						is_redirection_token(t_token_type type);
void					add_redir(t_astnode **first_redir_node,
							t_astnode **current, t_astnode *redir_node);
void					check_redirection_syntax(t_ma *ma);
void					process_redirection(t_astnode *node,
							t_astnode **last_word, t_astnode *redir_node,
							t_astnode **current);
void					parse_redirection_list(t_astnode *node,
							t_astnode **last_word, t_ma *ma);

int						is_word_token(t_token_type type);
void					add_word(t_astnode **first_word_node,
							t_astnode **current, t_astnode *word_node);
void					parse_word_list(t_astnode *node,
							t_astnode **last_word, t_ma *ma);

void					execute_ast(t_astnode *node, t_ma *ma);
void					handle_and_operator(t_astnode *node, t_ma *ma);
void					handle_or_operator(t_astnode *node, t_ma *ma);
void					execute_cmd_line(t_astnode *node, t_ma *ma);

void					setup_pipe(int pipe_fds[2]);
void					child_process(t_pip_args *a, t_astnode *simple_cmd,
							t_astnode *cmd_redir, t_ma *ma);
void					parent_process(t_pip_args *a);
void					create_process(t_pip_args *a, t_astnode *node,
							int i, t_ma *ma);
void					wait_for_all_processes(int cmd_count,
							pid_t *pid_arr, t_ma *ma);
void					execute_pipeline(t_astnode *node, t_ma *ma);

int						handle_redirections(t_astnode *redir_node,
							t_ma *ma);

int						redirect_output(char *file_name, int fd_num,
							t_ma *ma);
int						redirect_output_append(char *file_name, int fd_num,
							t_ma *ma);

int						redirect_input(char *file_name, t_ma *ma);
int						process_line(int fd, char *line, t_ma *ma);
int						write_to_tmp_file(int fd, const char *delimiter,
							t_ma *ma);
int						create_tmp_file(const char *temp_file_name,
							const char *delimiter, t_ma *ma);
int						handle_heredoc(const char *delimiter, t_ma *ma);

char					*give_tmp_name(t_ma *ma);
int						handle_env_variable(int fd, char *line, int *i,
							t_ma *ma);
int						handle_exit_status(int fd, char *line, int *i,
							t_ma *ma);

void					fill_delimiters(char ***delimiters_h,
							int *heredoc_f, t_ma *ma);
void					allocate_delimiters(char ***delimiters_h,
							int heredoc_count, t_ma *ma);
int						count_heredocs(t_ma *ma);
void					heredoc_checker(char ***delimiters_h,
							int *heredoc_f, t_ma *ma);
void					close_heredoc(char ***delimiters_h, int *heredoc_f,
							t_ma *ma);

int						node_word_count(t_astnode *node);
char					**create_words_arr(t_astnode *node, int *word_count,
							t_ma *ma);
void					execute_simple_cmd(t_astnode *node, t_ma *ma);
void					execute_words_arr(char **words_arr, t_ma *ma);

int						count_words(char **words_arr);
int						is_builtin(const char *word);
void					execute_builtin(char **args, t_ma *ma);

int						should_add_newline(char **args);
void					print_echo_args(char **args, int start_index);
void					builtin_echo(char **args, int word_count, t_ma *ma);

int						get_current_directory(char *current_dir);
char					*get_cd_path(char **args, t_env **env);
int						handle_cd_args(char **args, t_ma *ma);
int						update_env_variables(char *current_dir, t_ma *ma);
void					builtin_cd(char **args, t_ma *ma);

int						get_env_var(t_env **env, const char *name,
							char **value);
int						add_env_var(char *var, t_ma *ma);
int						update_oldpwd(char *current_dir, t_ma *ma);
int						update_pwd_value(int i, char *new_current_dir,
							t_ma *ma);
int						update_pwd(t_ma *ma);

int						check_valid_path(char *path);
char					*get_home_directory(t_env **env);
int						validate_cd_path(char *path);
int						change_directory(char *path);

void					builtin_pwd(char **args, t_ma *ma);

int						handle_var(char *var, t_ma *ma);
void					builtin_export(char **args, t_ma *ma);

int						add_env_var(char *var, t_ma *ma);
void					print_env_value(const char *env_value);
void					print_sorted_env(char **sorted_env, int count);
void					sort_env(char **sorted_env, int count);
void					print_env(t_env *env);

void					swap(char **a, char **b);
char					**copy_env(t_env *env);
int						find_env_var(t_env **env, char *var);
int						update_env_var(int i, const char *var, t_ma *ma);
int						is_valid_var(char *var);

int						find_env_var_u(t_env **env, char *var);
int						remove_env_var(t_env **env, char *var);
int						check_for_equal(char *str);
void					builtin_unset(char **args, t_ma *ma);

size_t					calculate_total_env_length(t_env *env);
char					*concatenate_env_vars(t_env *env,
							size_t total_length, t_ma *ma);
void					builtin_env(char **args, t_ma *ma);

long long				convert_to_ll(const char *str, int *i, int sign,
							int *error);
long long				ft_strtoll(const char *str, int *error);
int						checkoverflow(char *str);
int						validate_exit_args(char **args);
void					builtin_exit(t_ma *ma, char **args);

int						is_valid_argument(char *arg);
void					clean_exit(int exit_code, t_ma *ma);
int						skip_whitespace(const char *str, int i);
int						get_sign(const char *str, int *i);
int						is_number_argument(char *arg);

char					*join_path(const char *path, const char *cmd,
							t_ntc **first_node);
char					*check_path_access(char *path, char *cmd);
char					*search_in_paths(char **paths, char *cmd,
							t_ntc **first_node);
char					*find_command_path(char *cmd, t_env **env,
							int *p_ue, t_ntc **first_node);
void					execute_external_cmd(char **words_arr, t_env **env,
							t_ntc **first_node);

void					handle_permission_denied(char *cmd);
void					print_error(const char *msg, const char *arg);
void					handle_dot_and_double_dot(char **words_arr);
void					check_access_and_directory(const char *path);
void					check_command_errors(char *command_path,
							char **words_arr);

int						word_count(const char *s, char c);
char					*get_n_token(const char **s, char c,
							t_ntc **first_node);
char					**ft_split(char const *s, char c,
							t_ntc **first_node);

void					exit_or_setexit(int e, int e_flag, t_ma *ma);

/* t_env			*duplicate_vars(t_ntc **first_node, char **envp);
void						lexer(t_ma *ma);
int							count_tks(char const *s, char c);
int							handle_special_cases(const char *s, int *i);
int							handle_token_increments(const char *s, int *i);
char						**ft_split_tkns(char c, t_ma *ma);
t_token_type				clasify_token(char *value);
t_astnode					*parser(t_ma *ma);
t_astnode	*create_ast_node(t_ntc **first_node,
								t_nodetype type);
t_astnode					*parse_cmd_line(t_ma *ma);
void						get_next_token(t_ma *ma);
void						execute_builtin(char **args, t_ma *ma);
void						execute_ast(t_astnode *node, t_ma *ma);
void						execute_cmd_line(t_astnode *node, t_ma *ma);
void						execute_pipeline(t_astnode *node, t_ma *ma);
void						execute_simple_cmd(t_astnode *node, t_ma *ma);
void	execute_external_cmd(char **words_arr, t_env **env,
								t_ntc **first_node);
int							is_builtin(const char *word);
void						builtin_exit(t_ma *ma, char **args);
void						builtin_pwd(char **args, t_ma *ma);
void	builtin_echo(char **args, int count_words,
								t_ma *ma);
void						builtin_env(char **args, t_ma *ma);
void						builtin_export(char **args, t_ma *ma);
void						builtin_unset(char **args, t_ma *ma);
void						builtin_cd(char **args, t_ma *ma);
int							find_env_var(t_env **env, char *var);
pid_t						fork_process(void);
int							update_env_var(int i, const char *var, t_ma *ma);
int	handle_redirections(t_astnode *redir_node,
								t_ma *ma);
void						print_env(t_env *env);
char						**expand_wildcards_in_args(char **args, t_ma *ma);
int	expand_wildcard(t_wc_args *a, char *pattern,
								t_ma *ma);
int	add_single_element(t_wc_args *a, char *name,
								t_ma *ma);
int							match_pattern(const char *str, const char *pattern);
int							check_valid_file(char *path);
void						restore_io(t_ma *ma);
void						exit_or_setexit(int e, int e_flag, t_ma *ma);
void	generate_quotes(const char **s, char ***split,
								int *i, t_ma *ma);
void	generate_double_operators(const char **s,
								char ***split, int *i, t_ma *ma);
void	generate_single_operators_and_specials(const char **s,
								char ***split, int *i, t_ma *ma);
void	generate_regular_tkns(const char **s, char ***split,
								int *i, t_ma *ma);
char						*get_env(char *name, char **env);
void	handle_env_var(const char **s, char **result,
								t_ma *ma);
void						append_char(char s, char **result, t_ma *ma);
void	handle_quote_content(const char **s, char **result,
								char quote, t_ma *ma);
void	handle_newline_if_needed(const char **s,
								char **result, t_ma *ma);
int							check_valid_path(char *path);
char						*get_home_directory(t_env **env);
int							validate_cd_path(char *path);
int							change_directory(char *path);
int							update_env_variables(char *current_dir, t_ma *ma);
int	get_env_var(t_env **env, const char *name,
								char **value);
int							update_oldpwd(char *current_dir, t_ma *ma);
int							update_pwd(t_ma *ma);
void	close_heredoc(char ***delimiters_h, int *heredoc_f,
								t_ma *ma);
void	heredoc_checker(char ***delimiters_h,
								int *heredoc_f, t_ma *ma);
void	minishell_sort_str(char *tab[], size_t size); */

#endif