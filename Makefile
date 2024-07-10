CC		= cc
CFLAGS 	= -g -Wall -Wextra -Werror
RM		= rm -rf
LIBRARIES = -L./libft -lft
LIBRARIES_PATH = -I./libft/headers
LDFLAGS = -lreadline

SRCS 	= main.c lexer.c
SRCSB	= main.c lexer.c

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