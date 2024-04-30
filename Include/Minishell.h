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

typedef struct s_command
{
	int					isCommand;  	 // 1 if the input is a command, 0 otherwise 
    char				*command;  		 // The command to execute
    char				*arguments;     //The arguments to pass to the command
    struct	s_command	*next;
}			  			s_command;

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

void    init(s_input *terminal,s_command *command, char **env);
void	chekingInput(s_input *terminal, s_command *command);
void    printCommand(s_command *command);

#endif