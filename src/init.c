#include "../include/Minishell.h"

void	init(t_input *terminal, t_command *command)
{
	signal_check();
	init_terminal(terminal);
	init_command(command);
}

void	init_terminal(t_input *terminal)
{
	terminal->input = NULL;
	terminal->nb_cmd = 1;
	terminal->count_cmd = 0;
	terminal->echo.d_quotes = 0;
	terminal->echo.s_quotes = 0;
	terminal->echo.i = 0;
	terminal->echo.search_s2 = 0;
	terminal->echo.close = 0;
}	

void	init_command(t_command *command)
{
	// command->command = malloc(sizeof(char) * 100);
	// command->command[0] = '\0';
	// command->arguments = malloc(sizeof(char *) * 100);
	// command->arguments[0] = NULL;
	command->command = NULL;
	command->arguments = NULL;
	command->mem_cmd = 0;
	command->next = NULL;
	command->pipe = -1;
	command->redir_in = -1;
	command->redir_out = -1;
	command->hd_in = -1;
	command->hd_out = -1;
	command->builtins = 0;
	command->dollar = NULL;
	command->int_dollar = -1;
	command->out_dollar = NULL;
	command->args = 0;
	command->sd = 0;
}