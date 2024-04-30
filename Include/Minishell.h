#ifndef MINISHELL_H
#define MINISHELL_H

/*
*****************************************************
*                       INCLUDE                     
*****************************************************
*/

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
*****************************************************
                        STRUCT                     
*****************************************************
*/

typedef struct s_input
{
    char				*input;
}						s_input;

/*
*****************************************************
                        FUNCTION                     
*****************************************************
*/

void    init(s_input *terminal);

#endif