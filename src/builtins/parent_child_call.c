#include "../../include/Minishell.h"

extern int g_signal;

int	builtins_parent(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "export") == 0)
	{
	    ft_export(terminal, command);
	   	return (0);
	}
	else if (ft_strcmp(command->command, "unset") == 0)
	{
	    ft_unset(terminal, command);
	    return (0);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		return (0);
	}
	return (1);
}

int	builtins_child(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "export") == 0)
	{
	    ft_export(terminal, command);
	   	exit (0);
	}
	else if (ft_strcmp(command->command, "unset") == 0)
	{
	    ft_unset(terminal, command);
	    exit (0);
	}
	else if (ft_strcmp(command->command, "env") == 0)
	{
	    env(terminal);
	    exit (0);
	}
	return (builtins_child_2(terminal, command));
}

int	builtins_child_2(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		exit (0);
	}
	else if (ft_strcmp(command->command, "pwd") == 0)
	{
		ft_pwd(command);
		exit (0);
	}
	else if (ft_strcmp(command->command, "echo") == 0)
	{
		g_signal = ft_echo(terminal, command);
		exit (g_signal);
	}
	return (0);
}