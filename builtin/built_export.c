/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:50:56 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/07 11:34:43 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		env_swap(t_env_lst **curr, t_env_lst **prev, t_env_lst **begin, int i)
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

t_env_lst        *env_sort(t_env_lst *list, int i)
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

/*
int		print_sorted(t_env_lst *envlst)
{
	t_env_lst *begin;
	t_env_lst *export_cmd_lst;

	begin = ft_cmd_lstnew_env(envlst->name, envlst->content);
	export_cmd_lst = begin;
	envlst = envlst->next;
	while (envlst)
	{
		export_cmd_lst->next = ft_cmd_lstnew_env(envlst->name, envlst->content);
		export_cmd_lst = export_cmd_lst->next;
		envlst = envlst->next;
	}
	export_cmd_lst = env_sort(begin, 0);
	while (export_cmd_lst)
	{
		printf("%s=%s\n", export_cmd_lst->name, export_cmd_lst->content);
		export_cmd_lst = export_cmd_lst->next;
	}
	return (0);
}
int		export_var(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	*name;
	char	*content;
	int		i;
	int		j;
	char	**var;

	var = &lst->cmds[1];
	while (envlst->next)
		envlst = envlst->next;
	i = -1;
	while (var[++i])
	{
		j = 0;
		while (var[i][j] != '=')
			j++;
		name = ft_substr(var[i], 0, j);
		while (var[i][j])
			j++;
		content = ft_substr(ft_strchr(var[i], '=') + 1, 0, j);
		envlst->next = ft_cmd_lstnew_env(name, content);
		free(name);
		free(content);
		envlst = envlst->next;
	}
	return (0);
}

int		builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (!lst->cmds[1])
	{
		print_sorted(envlst);
		return (0);
	}
	else
		export_var(&lst->cmds, envlst);
	return (0);
}
*/