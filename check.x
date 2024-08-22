#include "minishell.h"

void lexer(t_ma *ma) {
    char **split;
    int i, j;
    char *concatenated_string;

    i = 0;
    j = 0;
    split = ft_split_tkns(' ', ma);

    while (split[i]) {
        // Check if the current token and the next one are both quoted strings
        if ((split[i][0] == '"' || split[i][0] == '\'') && 
            (split[i+1] && (split[i+1][0] == '"' || split[i+1][0] == '\''))) {
            
            // Concatenate them
            concatenated_string = concatenate_strings(split[i], split[i+1]);

            // Continue concatenating if more adjacent quoted strings are found
            while (split[i+2] && (split[i+2][0] == '"' || split[i+2][0] == '\'')) {
                char *temp = concatenate_strings(concatenated_string, split[i+2]);
                free(concatenated_string);
                concatenated_string = temp;
                i++;
            }

            ma->tkns[j] = g_c(&(ma->first_node), sizeof(t_token))->data;
            ma->tkns[j]->value = concatenated_string;
            ma->tkns[j]->type = clasify_token(ma->tkns[j]->value);
            j++;
            i++; // Skip the next token as it's already concatenated
        } else {
            ma->tkns[j] = g_c(&(ma->first_node), sizeof(t_token))->data;
            ma->tkns[j]->value = split[i];
            ma->tkns[j]->type = clasify_token(ma->tkns[j]->value);
            j++;
        }
        i++;
    }
    ma->tkns[j] = NULL;
    ma->c_tkn = ma->tkns;
    free_ntc_prior(&(ma->first_node), split);
}