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
	int					int_dollar; // 0 = $ // 1 = ? //
	int					pipe;
	int					*arg_q;
	int					redir_in;
	int					redir_out;
	int					hd_in; // 0 = >> // 1 = << //
	int					hd_out; // 0 = >> // 1 = << //
	int					builtins;
	int					mem_cmd;
	int					args;
	struct t_command	*next;
}				t_command;

// typedef struct t_count
// {
// 	int	args
// 	int	j;
// 	int	k;
// 	int	cmd_c;
// }				t_count;

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
	int cmd_c;
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

void	count_nb_args(t_input *terminal, t_command *command, t_parss *parss);
int	is_quote_nb_args(t_input *terminal, t_command *command, char c, int i);
int	is_quote(t_input *terminal, t_command *command, t_parss *parss);
int	is_quote_len(t_input *terminal, t_parss *parss, char c);
int	status_print(t_input *terminal);
void		printf_echo_s(t_input *terminal, t_command *command);
void	all_init_malloc(t_command *command, t_input *terminal, t_parss *parss);


/*
        Function List
*/

t_command	*ft_lstnew_m(void);
void		ft_lstadd_back_m(t_command **lst, t_command *new);
void		ft_lstclear_m(t_command *command, void (*del)(t_command *));
// void		del_command(t_command *command);

/*
        Function main
*/

int			white_space(char c);
int			find_p_r(char c);
void		init(t_input *terminal, t_command *command);
void		init_terminal(t_input *terminal);
void		init_command(t_command *command);
void 		free_nodes(t_command *first);
// void		checking_input(t_input *terminal, t_command *command);	


/*
        Function Executing
*/

char		**remove_empty_args(char **args);
char		*search_path(char **env, char *cmd_split);
void		executing(t_input *terminal, t_command *command);
void		exec_cmd(t_command *command, t_input *terminal);
void		exec_error(t_command *command, char *cmd_path, char **cmd_split);
void		args_alloc(t_command *command, char **cmd_split);
void		args_dup(t_command *command, char **cmd_split);

/*
		Function Executing pipes
*/

void		first_command(t_input *terminal, t_command *command, int i);
void		middle_command(t_input *terminal, t_command *command, int i);
void		last_command(t_input *terminal, t_command *command, int i);
void		only_one_command(t_input *terminal, t_command *command, int i);
void		parent_process(t_input *terminal, int i, pid_t pid);
void		calling_function(t_input *terminal, t_command *command, int i, int pid);
void    	redir_in(t_input *terminal, t_command *command, int i);
void   		redir_out(t_input *terminal, t_command *command, int i);
void    	here_out(t_input *terminal, t_command *command, int i);
void    	here_in(t_input *terminal, t_command *command, int i);
int   		verif_absolute_path(t_command *command);


/*
		Function Executing builtins
*/

int			builtins_check(t_command *command);
int			check_echo_args(t_command *command, t_input *terminal, int i, int valid);
int			ft_echo_check(char *s, char *s2, t_input *terminal,
				t_command *command);
char		*ft_quote(char *s, t_command *command);
int			quote_zero(char *s);
char		*put_all_that_shit(t_command *command);
char		*ft_put_arg_echo(char *s, int c);
char			ft_quote_close_verif(char *s, char around, char between);
int			builtins_parent(t_input *terminal, t_command *command);
int			ft_dollar_echo(t_input *terminal, char *arg, int there);
void		ft_call_dollar_env(t_input *terminal, char *dollar);
int			builtins_child(t_input *terminal, t_command *command);
int			builtins_child_2(t_input *terminal, t_command *command);
int			check_builtins_call(t_command *command);
int			builtins_call(t_input *terminal, t_command *command);
int			ft_echo(t_input *terminal, t_command *command);
void		printf_echo(char *s, char c, t_input *terminal, t_command *command);
void		ft_cd(t_command *command);
void		ft_pwd(t_command *command);
void		ft_exit(t_input *terminal, t_command *command);
void		init_export(t_input *terminal);
void		ft_export(t_input *terminal, t_command *command);
void		ft_unset(t_input *terminal, t_command *command);
void		init_env(t_input *terminal, char  **env);
void		env(t_input *terminal);
void		add_to_env(t_input *terminal, t_command *command, int arg_index);
int 		check_if_sort_export(char *str, char **env);
int 		check_alpha_export(char *str);
void 		print_export(t_input *terminal);
void		add_export(t_input *terminal, t_command *command, int arg_index);
// char		*create_new_str(char *str, char *equal_pos);
// void 		free_path_line(t_input *terminal);

/*
		Function signals
*/

void		signal_check(void);
void		handler_c(int signal);

/*
        Function parssing
*/

int			verif_input(t_input *terminal);
int 		check_char(char c);
void		check_redir(t_input *terminal, t_command *command, t_parss *parss);
void		call_redir_infile(t_input *terminal, t_command *command, t_parss *parss);
void		call_redir_outfile(t_input *terminal, t_command *command, t_parss *parss);
void		call_heredoc_in(t_input *terminal, t_command *command, t_parss *parss);
void		call_heredoc_out(t_input *terminal, t_command *command, t_parss *parss);
void		put_arg_cmd(t_input *terminal, t_command *command, t_parss *parss);
void		init_parss(t_parss *parss);
void		args_quote(t_input *terminal, t_command *command, t_parss *parss);
void		args_quotes(t_input *terminal, t_command *command, t_parss *parss);
void		cheking_input(t_input *terminal, t_command *command);
void 		call_dollar(t_input *terminal, t_command *command, t_parss *parss);
void	*search_path_dollar(t_input *terminal, t_command *command);
void	put_command(t_input *terminal, t_command *command, t_parss *parss);
// void		call_heredoc_infile(t_input *terminal, t_command *command, t_parss *parss);
// void		call_heredoc_outfile(t_input *terminal, t_command *command, t_parss *parss);
// void		call_dollar_interogation(t_input *terminal, t_command *command, t_parss *parss);
// void	*search_path_dollar_interogation(t_input *terminal);



/*
		Function Utils
*/

// void		print_commands(t_command *command);
// void		free_exec_cmd(t_command *command);
// void		free_cmd(t_command *command);
void		error_message(char *message);
void		advanced_print(t_command *command);
void		free_args(char **strtab);
void		free_exec_error(char *cmd_path, char **cmd_split);

#endif