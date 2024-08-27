CC		= cc
CFLAGS 	= -g -Wall -Wextra -Werror 
RM		= rm -rf
LIBRARIES = -L./libft -lft
LIBRARIES_PATH = -I./libft/headers
LDFLAGS = -lreadline

	
SRCS 	= 01-main.c \
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
		  31-wc_match_pattern.c\
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
		  31-wc_match_pattern.c 
		
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