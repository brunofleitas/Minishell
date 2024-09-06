#include "minishell.h"

void    heredoc_checker(char ***delimiters_h, int *heredoc_f, t_ma *ma)
{
    t_token **temp;
    int     heredoc_count;
    int     i;
    
    i = 0;
    heredoc_count = 0;
    *delimiters_h = NULL;
    temp = ma->tkns;

    while(temp[0])
    {
        if (temp[0]->type == TOKEN_HEREDOC)
            heredoc_count++;
        // write(2, temp[0]->value, ft_strlen(temp[0]->value));
        // write(2, "\n", 1);
        temp++;
    }
    temp = ma->tkns;
    if (!heredoc_count)
        return ;
    *delimiters_h = ft_calloc_g_c(heredoc_count + 1, sizeof(char *), &(ma->first_env));
    while(temp[0])
    {
        if (temp[0]->type == TOKEN_HEREDOC)
        { 
            temp++;
            delimiters_h[0][i] = ft_strdup_g_c(temp[0]->value, &(ma->first_env));
            (*heredoc_f)++;
            i++;
            return;
        }
        delimiters_h[0][i] = NULL;
        temp++;
    }
    return;
}

void close_heredoc(char ***delimiters_h, int *heredoc_f, t_ma *ma)
{
    int j = 0;

	if (ma->input && *delimiters_h && delimiters_h[0][j])
	{
        while(delimiters_h[j])
	    {
	    	if (ft_strcmp(ma->input, delimiters_h[0][j]) == 0)
	    	{	
	    		delimiters_h[0][j] = "empty000";
	    		(*heredoc_f)--;
                return;
	    	}
	    	j++;
	    }
    }
}