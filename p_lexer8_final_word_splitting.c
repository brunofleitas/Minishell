#include "minishell.h"

static int is_ifs_char(char c) {
    const char *ifs = getenv("IFS");
    if (!ifs)
        ifs = " \t\n";  // Default IFS
    return (strchr(ifs, c) != NULL);
}

static int count_words(const char *str) {
    int count = 0;
    int in_word = 0;
    while (*str) {
        if (is_ifs_char(*str)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
        str++;
    }
    return count;
}

static void split_token(t_tok *token, t_tok *new_tokens, int *new_count) {
    char *str = token->value;
    int start = 0;
    int i = 0;
    while (str[i]) {
        if (is_ifs_char(str[i])) {
            if (i > start) {
                new_tokens[(*new_count)++] = (t_tok){
                    .type = TOKEN_WORD,
                    .value = strndup(str + start, i - start),
                    .start_pos = token->start_pos + start,
                    .end_pos = token->start_pos + i - 1
                };
            }
            start = i + 1;
        }
        i++;
    }
    if (i > start) {
        new_tokens[(*new_count)++] = (t_tok){
            .type = TOKEN_WORD,
            .value = strndup(str + start, i - start),
            .start_pos = token->start_pos + start,
            .end_pos = token->end_pos
        };
    }
}

int final_word_splitting(t_tok *tokens, int token_count) {
    t_tok *new_tokens = malloc(sizeof(t_tok) * token_count * 10);
    int new_count = 0;

    for (int i = 0; i < token_count; i++) {
        if (tokens[i].type == TOKEN_WORD) {
            split_token(&tokens[i], new_tokens, &new_count);
        } else {
            new_tokens[new_count++] = tokens[i];
        }
    }

    memcpy(tokens, new_tokens, sizeof(t_tok) * new_count);
    free(new_tokens);
    return new_count;
}