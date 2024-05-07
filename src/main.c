#include "../Include/Minishell.h"

int	main(int ac, char **av, char **env)
{
    t_input		terminal;
    t_command	*command; 
    t_command	*first;

    command = malloc(sizeof(t_command));
    if (command == NULL) {
		printf("Error: malloc failed\n");
		return (1);
    }
	first = command;
    init(&terminal, command, env);
    while (1)
    {
        terminal.input = readline("\033[0;37m<3\033[0;31m   >\033[0;37m ");
        if (terminal.input[0] != '\0' && terminal.input[0] != '\n' && terminal.input[0] != '\t'
            && terminal.input[0] != ' ' && terminal.input[0] != '\v'
            && terminal.input[0] != '\f' && terminal.input[0] != '\r')
        {
            checking_input(&terminal, command);
            terminal.input_split = ft_split(terminal.input, ' ');
            command = first;
			print_commands(command);
            executing(&terminal, command);
			// printf("segfault?\n");
			// command = first;
			// ft_lstclear_m(command, del_command);
			command = malloc(sizeof(t_command));
			// if (command == NULL)
			// {
			// 	printf("Error: malloc failed\n");
			// 	return (1);
			// }
			command = first;
			command->next = NULL;
            // while (command->next != NULL)
            // {
            //     printCommand(command);
            //     command = command->next;
            // }
            // print_cheking(&terminal, command);
        }
        free(terminal.input);
    }
    return (0);
}

void print_commands(t_command *command)
{
	int i;
	int cmd_count;

	cmd_count = 0;
	while (command->next != NULL)
	{
		if (command->command[0] != '\0')
			printf("Commande[%d] = %s\n",cmd_count, command->command);
		i = 0;
		while (command->arguments[i] != NULL && command->arguments[i][0] != '\0')
		{
			printf("Arguments[%d] de la commande[%d] : %s\n",i, cmd_count, command->arguments[i]);
			i++;
		}
		printf("Pipe: %d\n", command->pipe);
		cmd_count++;
		command = command->next;
	}

}

void	init(t_input *terminal, t_command *command, char **env)
{
	terminal->input = NULL;
	terminal->env = env;
	command->command = malloc(sizeof(char) * 10000);
	command->command[0] = '\0';
	command->arguments = malloc(sizeof(char *) * 10000);
	command->arguments[0] = NULL;
	command->next = NULL;
	command->pipe = -1;
	terminal->nb_cmd = 1;
}

void	checking_input(t_input *terminal, t_command *command)
{
	int	i;
	int	j;
	int	k;
	int	input_length;
	int	token_index;

	i = -1;
	input_length = strlen(terminal->input); // ft_strlen(terminal->input);
	token_index = 0;
	if (!terminal->input)
		return ;
	while (i++ < input_length)
	{
		j = 0; // Reset j for each command
		while (i < input_length && terminal->input[i] == ' ')
			i++;
		while (i < input_length && white_space(terminal->input[i]) == 0
			&& find_pipe(terminal->input[i]) == 0)
		{
			command->command[j] = terminal->input[i];
			i++;
			j++;
		}
		command->command[j] = '\0';
		k = 0;
		command->arguments[k] = malloc(100 * sizeof(char));
		while (i < input_length && terminal->input[i] == ' ')
			i++;
		while (i < input_length && find_pipe(terminal->input[i]) == 0)
		{
			if (white_space(terminal->input[i]) == 1)
			{
				command->arguments[k][token_index] = '\0';
				token_index = 0;
				k++;
				command->arguments[k] = malloc(100 * sizeof(char));
			}
			else
			{
				command->arguments[k][token_index] = terminal->input[i];
				token_index++;
			}
			i++;
		}
		command->arguments[k][token_index] = '\0';
		command->arguments[k + 1] = NULL; // Null-terminate the arguments array
		if (terminal->input[i] == '|')
			command->pipe = 0;
		else if (terminal->input[i] == '<')
			command->pipe = 1;
		else if (terminal->input[i] == '>')
			command->pipe = 2;
		else
			command->pipe = -1;
		// printCommand(command);
		ft_lstadd_back_m(&command, ft_lstnew_m(NULL));
		command = command->next;
		i++;
	}
}


int	find_pipe(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
