/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 14:24:47 by lebourre          #+#    #+#             */
/*   Updated: 2021/07/20 15:51:25 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
t_env_lst	*env_copy(t_env_lst *src)
{
	t_env_lst *begin;

	begin =
}
*/

t_cmd_lst	*ft_new_cmd_list()
{
	t_cmd_lst	*new;

	new = malloc(sizeof(t_cmd_lst));
	if (new == NULL)
		return (NULL);
	new->cmd = "NIL";
	new->redir = NULL;
	new->fd[0] = 0;
	new->fd[1] = 0;
	new->next = NULL;
	return (new);
}

void	ft_env_remove_if(t_env_lst **begin_list, void *data_ref, int (*cmp)())
{
	t_env_lst	*list;
	t_env_lst	*tmp;

	list = *begin_list;
	while (list && list->next)
	{
		if ((*cmp)(list->next->name, data_ref) == 0)
		{
			tmp = list->next;
			list->next = list->next->next;
			free(tmp->name);
			free(tmp->content);
			free(tmp);
		}
		list = list->next;
	}
	list = *begin_list;
	if (list && (*cmp)(list->name, data_ref) == 0)
	{
		*begin_list = list->next;
		free(list->name);
		free(list->name);
		free(list);
	}
}
