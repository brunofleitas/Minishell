# include "ft_printf.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
    char    *key;
    char    *value;
}	t_word;

void    lexer(char *input);
int     count_words_tokens(char const *s, char c);
char    **ft_split_tokens(char const *s, char c);
