/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_sort.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 16:53:24 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 06:49:02 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env_swap(t_env_lst **curr, t_env_lst **prev, t_env_lst **begin, int i)
{
	t_env_lst	*swap;
	t_env_lst	*tmp_next;

	swap = *curr;
	tmp_next = swap->next->next;
	*curr = (*curr)->next;
	(*curr)->next = swap;
	(*curr)->next->next = tmp_next;
	if (i == 0)
		*begin = *curr;
	else
		(*prev)->next = *curr;
	*curr = *begin;
	return (0);
}

t_env_lst	*env_sort(t_env_lst *list, int i)
{
	t_env_lst	*curr;
	t_env_lst	*begin;
	t_env_lst	*prev;

	curr = list;
	begin = list;
	prev = list;
	while (curr->next)
	{
		if ((ft_strcmp(curr->name, curr->next->name)) > 0)
			i = env_swap(&curr, &prev, &begin, i);
		else
		{
			prev = curr;
			curr = curr->next;
			i++;
		}
	}
	return (begin);
}

int	builtin_export_sort(t_env_lst *e)
{
	t_env_lst	*begin;
	t_env_lst	*export_cmd_lst;

	begin = ft_lstnew_env(e->name, e->equal, e->content);
	export_cmd_lst = begin;
	e = e->next;
	while (e)
	{
		export_cmd_lst->next = ft_lstnew_env(e->name, e->equal, e->content);
		export_cmd_lst = export_cmd_lst->next;
		e = e->next;
	}
	export_cmd_lst = env_sort(begin, 0);
	while (export_cmd_lst)
	{
		printf("declare -x ");
		if (export_cmd_lst->content)
			printf("%s=\"%s\"\n", export_cmd_lst->name, export_cmd_lst->content);
		else if (export_cmd_lst->equal)
			printf("%s=\"\"\n", export_cmd_lst->name);
		else
			printf("%s\n", export_cmd_lst->name);
		export_cmd_lst = export_cmd_lst->next;
	}
	return (0);
}
