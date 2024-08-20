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

int	check_if_sort_export(char *str, char **env) //CORR
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 11;
	while (env[i])
	{
		j = 0;
		if (env[i][k] == str[j])
		{
			while (env[i][k] == str[j])
			{
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
	return (1);
}

void	ft_export(t_input *terminal, t_command *command)
{
	int	i;

	i = 0;
	if (command->arguments[0] == NULL)
		print_export(terminal);
	else
	{
		while (command->arguments[i])
		{
			if (check_if_sort_export(command->arguments[i], terminal->export)
				== 1
				&& check_alpha_export(command->arguments[i]) == 1)
			{
				printf("Adding %s to export\n", command->arguments[i]);
				add_export(terminal, command, i);
			}
			i++;
		}
	}
}

int	check_alpha_export(char *str) //CORR
{
	int	i;

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
			break ;
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
		terminal->export[i] = ft_strjoin_pipex("declare -x ", terminal->env[i]);
		i++;
		terminal->i++;
	}
	terminal->export[i] = NULL;
}

void    add_export(t_input *terminal, t_command *command, int arg_index)
{
	char	**tmp;
	int		i;
	char    *equal_sign;
	char    *new_str;

	printf("Nombre de ligne : %d\n", terminal->i);
	tmp = malloc(sizeof(char *) * (terminal->i + 1));
	if (tmp == NULL)
		return ;
	i = 0;
	while (terminal->export[i] != NULL)
	{
		tmp[i] = terminal->export[i];
		i++;
	}
	// equal_sign = malloc(sizeof (char *));
	free(terminal->export);
	equal_sign = ft_strchr(command->arguments[arg_index], '=');
	if (equal_sign != NULL) 
	{
		new_str = create_new_str(command->arguments[arg_index], equal_sign);
		tmp[i] = ft_strjoin_pipex("declare -x ", new_str);
		add_to_env(terminal, command, arg_index);
	}
	else
		tmp[i] = ft_strjoin_pipex("declare -x ", command->arguments[arg_index]);
	tmp[i] = NULL;
	terminal->export = tmp;
	terminal->i++;
}
