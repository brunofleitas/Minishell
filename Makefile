CC		= clang
CFLAGS 	= -g -Wall -Wextra -Werror 
RM		= rm -rf
LIBRARIES = -L./libft -lft
LIBRARIES_PATH = -I./libft/headers
LDFLAGS = -lreadline

SRCS 	= 1-main.c 2-build_env_structure.c 3-lexer.c 4-count_words.c\
		5-split_generator.c 6-clasify_token.c 7-AST_parser.c\
		8-AST_create_node.c 9-AST_functions.c 10-get_next_token.c\
		11-builtin_exit.c 12-builtin_cd.c 13-builtin_export.c 14-builtin_unset.c\
		15-builtin_echo.c 16-builtin_pwd.c 17-builtin_env.c\
		18-redirections.c 19-AST_execute.c 20-AST_execute_pipeline.c\
		21-AST_execute_simple_cmd.c 22-AST_execute_builtin.c\
		23-AST_execute_external_cmd.c 24-wc_expension.c 25-wc_expension_utils.c\
		26-wc_match_pattern.c
SRCSB 	= 1-main.c 2-build_env_structure.c 3-lexer.c 4-count_words.c\
		5-split_generator.c 6-clasify_token.c 7-AST_parser.c\
		8-AST_create_node.c 9-AST_functions.c 10-get_next_token.c\
		11-builtin_exit.c 12-builtin_cd.c 13-builtin_export.c 14-builtin_unset.c\
		15-builtin_echo.c 16-builtin_pwd.c 17-builtin_env.c\
		18-redirections.c 19-AST_execute.c 20-AST_execute_pipeline.c\
		21-AST_execute_simple_cmd.c 22-AST_execute_builtin.c\
		23-AST_execute_external_cmd.c 24-wc_expension.c 25-wc_expension_utils.c\
		26-wc_match_pattern.c
		
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