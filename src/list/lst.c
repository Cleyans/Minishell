/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brclemen <brclemen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:49:02 by brclemen          #+#    #+#             */
/*   Updated: 2024/06/06 05:47:55 by brclemen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Minishell.h"

void	ft_lstadd_back_m(t_command **lst, t_command *new)
{
	t_command	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

t_command	*ft_lstnew_m(void)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->command = NULL;
	new->arguments = NULL;
	new->pipe = -1;
	new->redir_in = -1;
	new->redir_out = -1;
	new->out_dollar = NULL;
	new->int_dollar = 0;
	new->dollar = NULL;
	new->builtins = 0;
	new->next = NULL;
	new->hd_in = -1;
	new->hd_out = -1;
	new->args = 0;
	return (new);
}

void	ft_lstclear_m(t_command *lst, void (*del)(t_command *))
{
	t_command	*current;

	if (!lst || !del)
		return ;
	while (lst)
	{
		current = lst;
		lst = current->next;
		(*del)(current);
	}
}

// void	del_command(t_command *command)
// {
// 	t_command	*cmd;

// 	cmd = (t_command *)command;
// 	free(cmd->arguments);
// 	free(cmd->command);
// 	free(cmd);
// }
