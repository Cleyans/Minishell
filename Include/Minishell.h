#ifndef MINISHELL_H
# define MINISHELL_H

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
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

/*
*****************************************************
                        STRUCT                     
*****************************************************
*/

typedef struct t_checking
{
	int	i;
	int	j;
	int	k;
	int	input_length;
	int	token_index;
}			  			t_checking;

typedef struct t_command
{
	int					isCommand;  	 // 1 if the input is a command, 0 otherwise 
	char				*command;  		 // The command to execute
	char				**arguments;     //The arguments to pass to the command
	int                 pipe;  		    // 0 if the command is followed by a pipe, 1 redirection < and 2 redirection >
	struct	t_command	*next;
}			  			t_command;

typedef	struct t_input
{
	char		*input;           // The input string
	char		**input_split;    // The input string split by pipe
	int		nb_cmd;   // the number of command
	int   	nb_pipe;  // the number of pipe
	char		**env;           // The environment variables
}			    t_input;

/*
*****************************************************
                        FUNCTION                     
*****************************************************
*/

void	init(t_input *terminal,t_command *command, char **env);
void	checking_input(t_input *terminal, t_command *command);
void	printCommand(t_command *command);
int		white_space(char c);
int		find_pipe(char c);
/*
        Function List
*/

void		ft_lstadd_back_m(t_command **lst, t_command *new);
void		del_command(t_command *command);
void		ft_lstclear_m(t_command *command, void (*del)(t_command *));
t_command	*ft_lstnew_m(void *content);

/*
        Function Executing
*/
char	*search_path(char **env, char *cmd_split);
void	executing(t_input *terminal, t_command *command);

void print_commands(t_command *command);

#endif