/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:46:24 by marvin            #+#    #+#             */
/*   Updated: 2024/06/13 12:46:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

int check_if_sort_export(char *str, char **env)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 11;
	while (env[i])
	{
		j = 0;
		if(env[i][k] == str[j])
		{
			// printf("%s\n", str);
			while (env[i][k] == str[j])
			{
				// printf("%c\n", str[j]);
				k++;
				j++;
				if (env[i][k] == '\0')
				{
					printf("Already in export\n");
					return (0);
				}
			}
			k = 11;
		}
		i++;
	}
	printf("Not in export\n");
	return(1);
}

void ft_export(t_input *terminal, t_command *command)
{
	if (command->arguments[0] == NULL)
		print_export(terminal);
	else
	{
		int i = 0;
		while (command->arguments[i])
		{
			if (check_if_sort_export(command->arguments[i], terminal->export) == 1 && check_alpha_export(command->arguments[i]) == 1)
			{
				printf("Adding %s to export\n", command->arguments[i]);
				add_export(terminal, command, i);
			}
			i++;
		}
	}
}

int check_alpha_export(char *str)
{
	int i;

	i = 0;
	if (ft_isalpha(str[i]) == 0 && str[i] != '_')
	{
		fprintf(stderr, "\033[0;35mMinihell\033[0;37m$\033[0m export: `%s': not a valid identifier\n", str);
		return (0);
	}
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			break;
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			fprintf(stderr, "\033[0;35mMinihell\033[0;37m$\033[0m export: `%s': not a valid identifier\n", str);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_export(t_input *terminal)
{
	int		i;
	// char	*equal_pos;
	// char	*new_str;
	terminal->i = 0;

	i = 0;
	while (terminal->env[i] != NULL)
		i++;
	terminal->export = malloc(sizeof(char *) * (i + 1));
	if (terminal->export == NULL)
		return ;
	i = 0;
	while (terminal->env[i] != NULL)
	{
	// 	equal_pos = ft_strchr(terminal->env[i], '=');
	// 	if (equal_pos != NULL)
	// 	{
	// 		new_str = create_new_str(terminal->env[i], equal_pos);
	// 		if (new_str == NULL)
	// 			return ;
	// 		terminal->export[terminal->i] = ft_strjoin_pipex("declare -x ", new_str);
	// 		free(new_str);
	// 	}
	// 	else
	// 		terminal->export[terminal->i] = ft_strjoin_pipex("declare -x ", terminal->env[i]);
	// 	terminal->i++;
		terminal->export[i] = ft_strjoin_pipex("declare -x ", terminal->env[i]);
		i++;
	}
}

void    add_export(t_input *terminal, t_command *command, int arg_index)
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
	equal_sign = malloc(sizeof(char) * 1);
	equal_sign = ft_strchr(command->arguments[arg_index], '=');
	if (equal_sign != NULL) 
	{
		new_str = create_new_str(command->arguments[arg_index], equal_sign);
		tmp[i] = ft_strjoin_pipex("declare -x ", new_str);
		add_to_env(terminal, command, arg_index); // Moved inside the if block
	}
	else
		tmp[i] = ft_strjoin_pipex("declare -x ", command->arguments[arg_index]);
	tmp[i + 1] = NULL;
	terminal->export = tmp;
	free(equal_sign);
	free(new_str);
	for (int j = 0; tmp[j]; j++)
		free(tmp[j]);
	terminal->i++;
	printf("Export added\n");
}
