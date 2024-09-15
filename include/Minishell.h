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

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

# define NOTCHILD -2

extern int g_signal;

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
	char				*infile;
	char				sd;
	char				*outfile;
	char				*word;
	int					fd;
	char				*dollar;
	char				*out_dollar;
	int					int_dollar;
	int					pipe;
	int					*arg_q;
	int					redir_in;
	int					redir_out;
	int					s_quotes;
	int					hd_in;
	int					hd_out;
	int					builtins;
	int					mem_cmd;
	int					args;
	struct t_command	*next;
}				t_command;

typedef struct t_echo
{
	int	i;
	int	len_s2;
	int	search_s2;
	int	s_quotes;
	int	d_quotes;
	int	close;
}				t_echo;

typedef struct t_parss
{
	int	i;
	int	j;
	int	k;
	int	cmd_c;
}				t_parss;

typedef struct t_input
{
	char		*input;
	int			nb_cmd;
	int			count_cmd;
	char		**env;
	char		**export;
	int			i;
	int			y;
	int			env_size;
	int			status;
	int			prev_fd;
	int			p_fd[4096][2];
	pid_t		pid[4096];
	t_parss		parss;
	t_echo		echo;
}				t_input;

/*
*****************************************************
                        FUNCTION                     
*****************************************************
*/

//NEW//

char		*get_env_value(t_input *terminal, char *var_name);
int			print_env_var(t_input *terminal, t_command *command, char *arg);
int		print_status(void);
void		handle_echo_argument(t_input *terminal, t_command *command, char *arg);
void	waitingall(t_input *terminal, pid_t *pid);


// CHATGPT FUNCTION EN HAUT

void		free_struct(t_input *terminal, t_command *command);
void 		free_terminal(t_input *terminal);
int			builtins_parent_s(t_input *terminal, t_command *command);
void		check_redirs(t_command *command);
void		child_process(t_input *terminal, t_command *command, int *p_fd, int i);
void   		parent_process(t_input *terminal, t_command *command, int *p_fd, pid_t *pid, int i);
void		count_nb_args(t_input *terminal, t_command *command);	
int			is_quote_nb_args(t_input *terminal, char c, int i);
int			is_quote(t_input *terminal, t_command *command, t_parss *parss);
int			is_quote_len(t_input *terminal, t_parss *parss, char c);
void		all_init_malloc(t_command *command, t_input *terminal);

/*
        Function List
*/

t_command	*ft_lstnew_m(void);
void		ft_lstadd_back_m(t_command **lst, t_command *new);
void		ft_lstclear_m(t_command *command, void (*del)(t_command *));

/*
        Function main
*/

int			white_space(char c);
int			find_p_r(char c);
void		init(t_input *terminal, t_command *command);
void		init_terminal(t_input *terminal);
void		init_command(t_command *command);
void		free_nodes(t_command *command);

/*
        Function Executing
*/

char		**remove_empty_args(char **args);
char		*search_path(char **env, char *cmd_split);
void		executing(t_input *terminal, t_command *command);
void		exec_cmd(t_command *command, t_input *terminal);
void		exec_error(t_command *command, char *cmd_path, char **cmd_split);
void		args_dup(t_command *command, char **cmd_split);

/*
		Function Executing pipes
*/

void		redir_in(t_command *command);
void		redir_out(t_command *command);
void		here_out(t_command *command);
void		here_in(t_command *command);
int			verif_absolute_path(t_command *command);

/*
		Function Executing builtins
*/

int			builtins_check(t_command *command);
int			builtins_parent(t_input *terminal, t_command *command);
int			ft_dollar_echo(t_input *terminal, char *arg, int there);
void		ft_call_dollar_env(t_input *terminal, char *dollar);
int			ft_echo(t_input *terminal, t_command *command);
void		ft_cd(t_command *command);
void		ft_pwd(t_command *command);
void		ft_exit(t_input *terminal, t_command *command);
void		init_export(t_input *terminal);
void		ft_export(t_input *terminal, t_command *command);
void		ft_unset(t_input *terminal, t_command *command);
void		init_env(t_input *terminal, char **env);
void		env(t_input *terminal);
void		add_to_env(t_input *terminal, t_command *command, int arg_index);
int			check_if_sort_export(char *str, char **env);
int			check_alpha_export(char *str);
void		print_export(t_input *terminal);
void		add_export(t_input *terminal, t_command *command, int arg_index);
char		*create_new_str(char *str, char *equal_pos);
void		remove_export_var(t_input *terminal, char *arg);

/*
		Function signals
*/

void		signal_check(void);
void		handler_c(int signal);

/*
        Function parssing
*/

int			verif_input(t_input *terminal);
int			check_char(char c);
void		check_redir(t_input *terminal, t_command *command, t_parss *parss);
void		call_redir_infile(t_input *terminal, t_command *command,
				t_parss *parss);
void		call_outfile(t_input *terminal, t_command *command, t_parss *parss);
void		call_heredoc_in(t_input *terminal, t_command *command,
				t_parss *parss);
void		call_heredoc_out(t_input *terminal, t_command *command,
				t_parss *parss);
void		put_arg_cmd(t_input *terminal, t_command *command, t_parss *parss);
void		init_parss(t_parss *parss);
void		args_quote(t_input *terminal, t_command *command, t_parss *parss);
void		args_quotes(t_input *terminal, t_command *command, t_parss *parss);
void		cheking_input(t_input *terminal, t_command *command);
void		call_dollar(t_input *terminal, t_command *command, t_parss *parss);
void		*search_path_dollar(t_input *terminal, t_command *command);
void		put_command(t_input *terminal, t_command *command, t_parss *parss);

/*
		Function Utils
*/

void		error_message(char *message);
void		advanced_print(t_command *command);
void		advanced_print_deux(t_command *command);
void		free_args(char **strtab);
void		free_exec_error(char *cmd_path, char **cmd_split);

#endif