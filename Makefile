CC		= cc
CFLAGS 	= -g -Wall -Wextra -Werror
RM		= rm -rf
LIBRARIES = -L./libft -lft
LIBRARIES_PATH = -I./libft/headers
LDFLAGS = -lreadline

SRCS 	= 1-main.c 2-lexer.c 3-count_words.c 4-split_generator.c 5-clasify_token.c 6-parser.c 7-AST_functions.c 8-get_next_token.c
SRCSB	= 1-main.c 2-lexer.c 3-count_words.c 4-split_generator.c 5-clasify_token.c 6-parser.c 7-AST_functions.c 8-get_next_token.c

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

.PHONY: all bonus clean fclean re