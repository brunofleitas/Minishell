
#define MAX_TOK_LEN 1024

typedef enum e_tok_typ
{
    TOKEN_WORD,
    TOKEN_SPECIAL_CHAR,
    TOKEN_QUOTE,
    TOKEN_VARIABLE,
    TOKEN_COMMAND_SUBSTITUTION,
    TOKEN_ARITHMETIC_EXPANSION
}   t_tok_type;

typedef struct s_token
{
    t_tok_type   type;
    char        *value;
    int         start_pos;
    int         end_pos;
}               t_tok;

t_tok   *tokenize(char *input, t_ma *ma);
void    initial_tokenization(char *input, int start, t_ma *ma);
void    handle_quotes_and_escapes(char *input, int start, t_ma *ma);
void    handle_variables_and_substitutions(char *input, int start, t_ma *ma);
void    handle_special_characters(char *input, int start, t_ma *ma);
void    combine_tokens(t_ma *ma);
void    handle_globbing(char *input, t_ma *ma);
int     match_pattern(const char *filename, const char *pattern);
int     expand_wildcard(t_wc_args *a, char *pattern, t_ma *ma);
int     add_single_element(t_wcs_args *a, char *full_path, t_ma *ma);
int     add_matching_entry(t_wcs_args *a, char *dir_path, char *entry_name, t_ma *ma);
void    final_word_splitting(t_ma *ma);