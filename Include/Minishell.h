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
# include "Libft/libft.h"

/*
*****************************************************
                        STRUCT                     
*****************************************************
*/

typedef struct s_checking
{
    int i;
    int j;
    int k;
    int input_length;
    int token_index;
}			  			s_checking;

typedef struct t_command
{
	int					isCommand;  	 // 1 if the input is a command, 0 otherwise 
    char				*command;  		 // The command to execute
    char				**arguments;     //The arguments to pass to the command
    int                 pipe;  		 // 0 if the command is followed by a pipe, 1 redirection < and 2 redirection >
    struct	t_command	*next;
}			  			t_command;

typedef	struct s_input
{
	char		*input;     // The input string
	char		**stockCommand;   // The command to execute
	char		**env;      // The environment variables
}			    s_input;

/*
*****************************************************
                        FUNCTION                     
*****************************************************
*/

void    init(s_input *terminal,t_command *command, char **env);
void    checkingInput(s_input *terminal, t_command *command);
void    printCommand(t_command *command);
char check_arg(s_input *terminal);
int white_space(char c);
int find_pipe(char c);
/*
        Function List
*/
void	ft_lstadd_back_m(t_command **lst, t_command *new);
t_command	*ft_lstnew_m(void *content);


#endif