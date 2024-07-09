#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
    char    *key;
    char    *value;
}	t_word;

int	count_words(char const *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_strtrim(char const *s1, char const *set);
char	*ft_strdup(const char *s);
void    lexer(char *input);