/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:22:13 by brclemen          #+#    #+#             */
/*   Updated: 2024/05/10 09:22:13 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h" //CORR

int	ft_echo(t_input *terminal, t_command *command)
{
	int i;
	int newline_flag;

	newline_flag = 1;
	i = 0;
	if (command->arguments && ft_strcmp(command->arguments[i], "-n") == 0)
	{
		newline_flag = 0;
		i++;
	}
	while (command->arguments && command->arguments[i])
	{
		handle_echo_argument(terminal, command, command->arguments[i]);
		if (command->arguments[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline_flag)
		write(1, "\n", 1);
	return (0);
}

void	handle_echo_argument(t_input *terminal, t_command *command, char *arg)
{
	int j;

	j = 0;
	if (arg[j] == '$' && arg[j + 1] == '\0')
	{
		write(1, "$", 1);
		return;
	}
	while (arg[j])
	{
		if (arg[j] == '$' && arg[j + 1] == '?' && command->s_quotes != 1)
			j += print_status();
		else if (arg[j] == '$' && arg[j + 1] == ' ' && command->s_quotes != 1)
			j = j + write(1, "$", 1);
		else if (arg[j] == '$' && (command->s_quotes != 1))
			j += print_env_var(terminal, command, arg + j);
		else
			j = j + write(1, &arg[j], 1);
	}
}

int	print_status(void)
{
	char *status;
	if (g_signal != 256)
		status = ft_itoa(g_signal);
	else
		status = "1";
	write(1, status, ft_strlen(status));
	free(status);
	return (2);
}

int	print_env_var(t_input *terminal, t_command *command, char *arg)
{
	int 	len;
	char	*var_name;
	char	*var_value;

	len = 1;
	while (arg[len] && arg[len] != ' ') // Trouver la fin de la variable
	{
		if (arg[len] == '$' || arg[len + 1] == '?')
		{
			len++;
			break;
		}
		len++;
	}
	if (command->s_quotes == 1)
	{
		var_name = ft_substr(arg, 0, len);
		var_value = var_name;
	}
	else
	{
		var_name = ft_substr(arg, 1, len - 1); // Récupérer le nom de la variable sans le $
		var_value = get_env_value(terminal, var_name); // Obtenir la valeur correspondante dans l'environnement
	}
	if (var_value)
		write(1, var_value, ft_strlen(var_value)); // Afficher la valeur de la variable
	free(var_name);
	return (len); // Retourner la longueur de la variable traitée
}

// Fonction pour obtenir la valeur d'une variable d'environnement
char	*get_env_value(t_input *terminal, char *var_name)
{
	int		i;
	int		name_len;

	if (!var_name)
		return (NULL);

	i = 0;
	name_len = ft_strlen(var_name);
	while (terminal->env[i])
	{
		// Comparer jusqu'à '=' pour trouver la variable dans l'environnement
		if (ft_strncmp(var_name, terminal->env[i], name_len) == 0 && terminal->env[i][name_len] == '=')
			return (terminal->env[i] + name_len + 1); // Retourner la valeur après '='
		i++;
	}
	return (NULL); // Retourner NULL si la variable n'est pas trouvée
}
