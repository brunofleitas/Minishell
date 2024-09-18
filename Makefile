CC		= cc
CFLAGS 	= -g -Wall -Wextra -Werror 
RM		= rm -rf
LIBRARIES = -L./libft -lft
LIBRARIES_PATH = -I./libft/headers
LDFLAGS = -lreadline

	
SRCS 	= 01-main.c \
		  02-restore_io.c \
		  03-build_env_structure.c \
		  04-lexer.c \
		  05-count_words.c \
		  06-count_words_utils.c \
		  07-split_generator.c \
		  08-generate_quotes.c \
		  09-generate_quotes_utils.c \
		  10-generate_double_operators.c \
		  11-generate_single_and_specials.c \
		  12-generate_regular.c \
		  13-generate_regular_utils.c \
		  14-wc_expension.c \
		  15-wc_expension_utils.c \
		  16-wc_match_pattern.c \
		  17-minishell_sorting.c \
		  18-clasify_token.c \
		  19-get_next_token.c \
		  20-AST_create_node.c \
		  21-AST_parser.c \
		  22-AST_parse_cmd_line.c \
		  23-AST_parse_pipeline.c \
		  24-AST_parse_cmd.c \
		  25-AST_parse_simple_cmd.c \
		  26-AST_parse_redirections.c \
		  27-AST_parse_word.c \
		  28-AST_execute.c \
		  29-AST_execute_pipeline.c \
		  30-handle_redirections.c \
		  31-handle_output.c \
		  32-handle_input.c \
		  33-handle_input_utils.c \
		  34-handle_heredoc.c \
		  35-AST_execute_simple_cmd.c \
		  36-AST_execute_builtin.c \
		  37-builtin_echo.c \
		  38-builtin_cd.c \
		  39-builtin_cd_env_vars.c \
		  40-builtin_cd_utils.c \
		  41-builtin_pwd.c \
		  42-builtin_export.c \
		  43-builtin_export_print_vars.c \
		  44-builtin_export_utils.c \
		  45-builtin_unset.c \
		  46-builtin_env.c \
		  47-builtin_exit.c \
		  48-builtin_exit_utils.c \
		  49-AST_execute_external_cmd.c \
		  50-AST_execute_ext_cmd_errors.c \
		  50-AST_execute_ext_cmd_utils.c \
		  51-exit_setexit.c \
		  get_next_line.c

SRCSB 	= 01-main.c \
		  02-build_env_structure.c \
		  03-lexer.c \
		  04-count_words.c \
		  05-count_words_utils.c \
		  06-split_generator.c \
		  07-token_generators.c \
		  08-token_utils.c \
		  09-clasify_token.c \
		  10-AST_parser.c \
		  11-AST_create_node.c \
		  12-AST_functions.c \
		  14-get_next_token.c\
		  15-builtin_cd.c \
		  16-builtin_cd_utils.c \
		  17-builtin_export.c \
		  18-builtin_unset.c \
		  19-builtin_echo.c \
		  20-builtin_pwd.c \
		  21-builtin_env.c \
		  22-builtin_exit.c \
		  23-redirections.c \
		  24-AST_execute.c \
		  25-AST_execute_pipeline.c \
		  26-AST_execute_simple_cmd.c \
		  27-AST_execute_builtin.c \
		  28-AST_execute_external_cmd.c \
		  29-wc_expension.c \
		  30-wc_expension_utils.c\
		  31-wc_match_pattern.c \
		  32-restore_io.c
		
OBJS	= $(SRCS:.c=.o)
OBJSB	= $(SRCSB:.c=.o)

NAME	= minishell
BONUS	= minishell_bonus

LIBFT     = libft/libft.a

all: $(NAME)

bonus: $(BONUS)

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(LIBRARIES_PATH) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	cc get_next_line.c -c
	$(CC) $(CFLAGS) $(OBJS) $(LIBRARIES) -o $(NAME) $(LDFLAGS)

$(BONUS): $(OBJSB) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJSB) $(LIBRARIES) -o $(BONUS) $(LDFLAGS)

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS) $(OBJSB)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME) $(BONUS)

re: fclean all
	$(MAKE) -C libft clean
	$(RM) $(OBJS) $(OBJSB)

.PHONY: all bonus clean fclean re