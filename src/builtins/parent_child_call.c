#include "../../include/Minishell.h"

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
	else if (ft_strcmp(command->command, "env") == 0)
	{
	    env(terminal);
	    return (1);
	}
	builtins_parent_2(terminal, command);
	return (0);
}

int	builtins_parent_2(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "pwd") == 0)
	{
		ft_pwd(command);
		return (1);
	}
	else if (ft_strcmp(command->command, "echo") == 0)
	{
		ft_echo(terminal, command);
		return (1);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	return (0);
}

int	builtins_child(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "export") == 0)
	{
	    ft_export(terminal, command);
	   	exit (1);
	}
	else if (ft_strcmp(command->command, "unset") == 0)
	{
	    ft_unset(terminal, command);
	    exit (1);
	}
	else if (ft_strcmp(command->command, "env") == 0)
	{
	    env(terminal);
	    exit (1);
	}
	builtins_child_2(terminal, command);
	return (0);
}

int	builtins_child_2(t_input *terminal, t_command *command)
{
	if (ft_strcmp(command->command, "cd") == 0)
	{
		ft_cd(command);
		exit (1);
	}
	else if (ft_strcmp(command->command, "pwd") == 0)
	{
		ft_pwd(command);
		exit (1);
	}
	else if (ft_strcmp(command->command, "echo") == 0)
	{
		ft_echo(terminal, command);
		exit (1);
	}
	else if (ft_strcmp(command->command, "exit") == 0)
		ft_exit(terminal, command);
	return (0);
}