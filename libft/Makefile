# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcasagra <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/28 16:43:56 by pcasagra          #+#    #+#              #
#    Updated: 2024/02/28 16:43:57 by pcasagra         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				= cc
CFLAGS			= -g -Wall -Werror -Wextra
RM				= rm -rf
ARCHIVE			= ar rcs
LIBRARIES_PATH	= -I./headers

SRCS_BASIC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	  		ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	  		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	  		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	  		ft_atoi.c ft_calloc.c ft_calloc_g_c.c ft_realloc_g_c.c ft_strdup_g_c.c ft_substr_g_c.c \
			ft_strjoin_g_c.c ft_strtrim_g_c.c ft_split_g_c.c ft_itoa_g_c.c \
			ft_strmapi_g_c.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c \
	  		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	  		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
	  		ft_lstmap_g_c.c ft_strcmp.c P_g_c.c

SRCS_PRINTF = fill_ot_buffer.c flush_buffers.c ft_printf.c \
			g_calculate_width_pad.c g_handle_all_n.c g_handle_only_flags.c \
			g_handle_precision_s_us.c g_handle_width_s_us.c \
			j_extract_format.c j_store_flags.c j_store_precision.c \
			j_store_specifier.c j_store_width.c k_get_output_type.c \
			k_mini_itoa.c o_c_format.c o_n_format.c o_s_format.c \
			r_s_to_substr.c r_abs_to_substr.c r_pad_num.c r_prefix_num.c \
			structure_initialization.c substring_creation.c

OBJS_BASIC	= $(SRCS_BASIC:.c=.o)
OBJS_PRINTF	= $(SRCS_PRINTF:.c=.o)

NAME	= libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(LIBRARIES_PATH) -c $< -o $@

$(NAME): $(OBJS_BASIC) $(OBJS_PRINTF)
	$(ARCHIVE) $(NAME) $(OBJS_BASIC) $(OBJS_PRINTF)

clean:
	$(RM) $(OBJS_BASIC) $(OBJS_PRINTF)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
