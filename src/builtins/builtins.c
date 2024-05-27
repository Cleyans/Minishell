/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 05:52:36 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/09 05:52:36 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	builtins_child(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "echo") == 0)
	{
		ft_echo(terminal, command);
		exit(1);
	}
}

int	builtins_parent(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "export") == 0)
	{
	    ft_export(terminal, command);
	    return (1);
	}
	else if (ft_strcmp(command->command, "unset") == 0)
	{
	    ft_unset(terminal, command);
	    return (1);
	}
	// else if (ft_strcmp(command->command, "env") == 0)
	// {
	//     ft_env(command);
	//     return (1);
	// }
	else if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "pwd") == 0)
	{
		ft_pwd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	return (0);
}

void	ft_cd(t_command *command) // ne pas oublier le status
{
	char	*path;

	if (command->arguments[0] == NULL)
	{
		path = getenv("HOME");
		if (chdir(path) == -1)
		{
			fprintf(stderr, "Minishell: cd: %s:\
 No such file or directory\n", path);
			return ;
		}
	}
	else
	{
		if (chdir(command->arguments[0]) == -1)
		{
			fprintf(stderr, "Minishell: cd: %s: No such file or\
 directory\n", command->arguments[0]);
			return ;
		}
	}
}

void	ft_pwd(t_command *command) // ne pas oublier le status
{
	char	*buffer;
	int		buffer_size;

	buffer_size = 1024;
	buffer = malloc(sizeof(char) * buffer_size);
	if (command->arguments[0] != NULL)
	{
		fprintf(stderr, "Error: pwd: too many arguments\n");
		return ;
	}
	if (buffer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		return ;
	}
	if (getcwd(buffer, 1024) == NULL)
	{
		fprintf(stderr, "Error: getcwd failed\n");
		free(buffer);
		return ;
	}
	ft_printf("%s\n", buffer);
	free(buffer);
}

void init_export(t_input *terminal) 
{
	int i;
	
	i = 0;
	while(terminal->env[i] != NULL)
		i++;
	terminal->export = malloc(sizeof(char *) * (i + 1));
	if (terminal->export == NULL)
		return ;
	i = 0;

	while (terminal->env[i] != NULL)
	{
		terminal->export[terminal->i] = ft_strjoin_pipex("declare -x ", terminal->env[i]);
		terminal->i++;
		i++;
	}
}


void print_export(t_input *terminal)
{
	int i;

	i = 0;
	while (terminal->export[i] != NULL)
	{
		printf("%s\n", terminal->export[i]);
		i++;
	}
}

static void	add_export(t_input *terminal, t_command *command, int arg_index)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (terminal->i + 2));
	if (tmp == NULL) {
		return;
	}

	i = 0;
	while (terminal->export[i] != NULL)
	{
		tmp[i] = terminal->export[i];
		i++;
	}
	free(terminal->export);
	tmp[i] = ft_strjoin_pipex("declare -x ", command->arguments[arg_index]);
	tmp[i + 1] = NULL;
	terminal->export = tmp;
	terminal->i++;
}

void	ft_export(t_input *terminal, t_command *command)
{
	if (command->arguments[0] == NULL)
		print_export(terminal);
	else
	{
		int i = 0;
		while (command->arguments[i])
		{
			add_export(terminal, command, i);
			i++;
		}
	}
}

// void free_path_line(t_input *terminal)
// {
// 	if (terminal->path[j] != NULL)
// 	{
// 		free(terminal->path[j]);
// 		while (terminal->path[j] != NULL)
// 		{
// 			terminal->path[j] = terminal->path[j + 1];
// 			j++;
// 		}
// 		terminal->path[j - 1] = NULL;
// 	}
// }

void	ft_unset(t_input *terminal, t_command *command)
{
	int		i;
	int		j;
	char	*arg_start;
	char	*prefix = "declare -x ";

	i = 0;
	while (command->arguments[i] != NULL)
	{
		j = 0;
		while (terminal->export[j] != NULL)
		{
			arg_start = terminal->export[j] + strlen(prefix);
			if (strncmp(arg_start, command->arguments[i], strlen(command->arguments[i])) == 0 && 
				(arg_start[strlen(command->arguments[i])] == '=' || arg_start[strlen(command->arguments[i])] == '\0'))
			{
				if (terminal->export[j] != NULL)
				{
					free(terminal->export[j]);
				}
				while (terminal->export[j] != NULL)
				{
					terminal->export[j] = terminal->export[j + 1];
					j++;
				}
				terminal->export[j - 1] = NULL;
				terminal->i--;
				// if (arg_start[strlen(command->arguments[i])] == '=')
				// {
				// 	free_path_line(terminal);
				// }
				break;
			}
			j++;
		}
		i++;
	}
}

void init_env(t_input *terminal, char  **env)
{
	if(env != NULL)
	{
		int i ;
		
		i = 0;
		while (env[i] != NULL)
			i++;
		terminal->env = malloc(sizeof(char *) * (i + 1));
		if (terminal->env == NULL)
			return ;
		i = 0;
		while (env[i] != NULL)
		{
			terminal->env[i] = ft_strdup(env[i]);
			i++;
		}
		terminal->env[i] = NULL;
		i = 0;
		while(terminal->env[i] != NULL)
		{
			printf("%s\n", terminal->env[i]);
			i++;
		}
	}
}