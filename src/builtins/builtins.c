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

char	*create_new_str(char *str, char *equal_pos)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc((equal_pos - str) + ft_strlen(equal_pos) + 3); // For "" and '\0'
	if (new_str == NULL)
		return (NULL);
	
	i = 0;
	while (str + i != equal_pos)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i++] = '=';
	new_str[i++] = '"';
	j = 0;
	while (equal_pos[j + 1] != '\0')
	{
		new_str[i] = equal_pos[j + 1];
		i++;
		j++;
	}
	new_str[i++] = '"';
	new_str[i] = '\0';
	return (new_str);
}

void	init_export(t_input *terminal)
{
	int		i;
	char	*equal_pos;
	char	*new_str;

	i = 0;
	while (terminal->env[i] != NULL)
		i++;
	terminal->export = malloc(sizeof(char *) * (i + 1));
	if (terminal->export == NULL)
		return ;
	i = 0;
	while (terminal->env[i] != NULL)
	{
		equal_pos = ft_strchr(terminal->env[i], '=');
		if (equal_pos != NULL)
		{
			new_str = create_new_str(terminal->env[i], equal_pos);
			if (new_str == NULL)
				return ;
			terminal->export[terminal->i] = ft_strjoin_pipex("declare -x ", new_str);
			free(new_str);
		}
		else
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
	char    *equal_sign;
	char    *new_str;

	tmp = malloc(sizeof(char *) * (terminal->i + 2));
	if (tmp == NULL)
		return ;
	i = 0;
	while (terminal->export[i] != NULL)
	{
		tmp[i] = terminal->export[i];
		i++;
	}
	free(terminal->export);
	equal_sign = ft_strchr(command->arguments[arg_index], '=');
	if (equal_sign != NULL) 
	{
		new_str = create_new_str(command->arguments[arg_index], equal_sign);
		tmp[i] = ft_strjoin_pipex("declare -x ", new_str);
		free(new_str);
		add_to_env(terminal, command, arg_index); // Moved inside the if block
	}
	else
	{
		tmp[i] = ft_strjoin_pipex("declare -x ", command->arguments[arg_index]);
	}
	tmp[i + 1] = NULL;
	terminal->export = tmp;
	terminal->i++;
}

void	add_to_env(t_input *terminal, t_command *command, int arg_index)
{
	terminal->env = realloc(terminal->env, (terminal->env_size + 2) * sizeof(char *));
	if (terminal->env == NULL)
		return ;
	terminal->env[terminal->env_size] = ft_strdup(command->arguments[arg_index]);
	terminal->env[terminal->env_size + 1] = NULL;
	terminal->env_size++;
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

static void	unset_env(t_input *terminal, char *arg)
{
	int		j;
	char	*arg_start;

	j = 0;
	while (terminal->env[j] != NULL)
	{
		arg_start = terminal->env[j];  // Use terminal->env[j] instead of terminal->export[j]
		if (ft_strncmp(arg_start, arg, ft_strlen(arg)) == 0 &&
			(arg_start[ft_strlen(arg)] == '=' || arg_start[ft_strlen(arg)] == '\0'))
		{
			free(terminal->env[j]);
			while (terminal->env[j] != NULL)
			{
				terminal->env[j] = terminal->env[j + 1];
				j++;
			}
			terminal->env[j - 1] = NULL;
			terminal->env_size--;
			break;
		}
		j++;
	}	
}


void		ft_unset(t_input *terminal, t_command *command)
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
			arg_start = terminal->export[j] + ft_strlen(prefix);
			if (ft_strncmp(arg_start, command->arguments[i], ft_strlen(command->arguments[i])) == 0 &&
				(arg_start[ft_strlen(command->arguments[i])] == '=' || arg_start[ft_strlen(command->arguments[i])] == '\0'))
			{
				free(terminal->export[j]);
				while (terminal->export[j] != NULL)
				{
					terminal->export[j] = terminal->export[j + 1];
					j++;
				}
				terminal->export[j - 1] = NULL;
				terminal->i--;
				break;
			}
			j++;
		}
		// Always call unset_env, regardless of whether command->arguments[i] contains '='
		unset_env(terminal, command->arguments[i]);
		i++;
	}
}

void init_env(t_input *terminal, char  **env)
{
	terminal->env_size = 0;
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
			terminal->env[terminal->env_size] = ft_strdup(env[i]);
			i++;
			terminal->env_size++;
		}
		terminal->env[terminal->env_size] = NULL;
		i = 0;
	}
}

void	env(t_input *terminal)
{
	int i;

	i = 0;
	while (terminal->env[i] != NULL)
	{
		printf("%s\n", terminal->env[i]);
		i++;
	}
}