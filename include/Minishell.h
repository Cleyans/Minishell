/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 05:43:20 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 05:43:20 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
*****************************************************
*                       INCLUDE                     
*****************************************************
*/

# include "Libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

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
}				t_checking;

typedef struct t_command
{
	char				*command;
	char				**arguments;
	int					pipe;
	int					builtins;
	struct t_command	*next;
}				t_command;

typedef struct t_input
{
	char		*input;
	int			nb_cmd;
	char		**env;
	int			status;
	int			p_fd[4096][2];
	pid_t		pid[4096];
}				t_input;

/*
*****************************************************
                        FUNCTION                     
*****************************************************
*/

/*
        Function main
*/

void	init(t_input *terminal, t_command *command, char **env);
void	checking_input(t_input *terminal, t_command *command);
int		white_space(char c);
int		find_pipe(char c);

/*
        Function List
*/

t_command	*ft_lstnew_m(void);
void	ft_lstadd_back_m(t_command **lst, t_command *new);
// void		del_command(t_command *command);
void	ft_lstclear_m(t_command *command, void (*del)(t_command *));

/*
        Function Executing
*/

char	*search_path(char **env, char *cmd_split);
void	executing(t_input *terminal, t_command *command);
void	exec_cmd(t_command *command, t_input *terminal);
char	**remove_empty_args(char **args);

/*
		Function Executing pipes
*/

void	first_command(t_input *terminal, t_command *command, int i);
void	middle_command(t_input *terminal, t_command *command, int i);
void	last_command(t_input *terminal, t_command *command, int i);
void	only_one_command(t_input *terminal, t_command *command, int i);
void	parent_process(t_input *terminal, int i, pid_t pid);
void	calling_function(t_input *terminal, t_command *command, int i);

/*
		Function Executing Redirection
*/

// void    redirection_input(t_input *terminal, t_command *command, int i);
// void    redirection_output(t_input *terminal, t_command *command, int i);

/*
		Function Executing builtins
*/

int		builtins_parent(t_input *terminal, t_command *command);
void	builtins_child(t_command *command);
void	ft_echo(t_command *command);
void	ft_cd(t_command *command);
void	ft_pwd(t_command *command);
void	ft_exit(t_input *terminal, t_command *command);

/*
		Function Error
*/

void	error_message(char *message);

/*
        Function parssing
*/

int		verif_input(t_input *terminal);

/*
		Function Utils
*/

void	print_commands(t_command *command);
void	free_exec_cmd(t_command *command);
void	free_exec_error(t_command *command, char *cmd_path, char **cmd_split);

#endif