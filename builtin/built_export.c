/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:18 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/27 18:46:35 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	export_cat(t_env_lst **list, char *str, char *tmp, char *content)
{
	content = ft_substr(ft_strchr(str, '=') + 1, 0,
			ft_strlen(ft_strchr(str, '=') + 1));
	if (content == NULL)
	{
		ft_putstr_fd("error: fatal\n", 2);
		return (1);
	}
	if ((*list)->content == NULL)
	{
		(*list)->content = content;
		return (0);
	}
	tmp = (*list)->content;
	(*list)->content = ft_strjoin((*list)->content, content);
	if ((*list)->content == NULL)
	{
		ft_putstr_fd("error: fatal\n", 2);
		free(tmp);
		return (1);
	}
	if ((*list)->equal == 0)
		(*list)->equal = 1;
	free(tmp);
	return (0);
}

int	export_add(t_env_lst **list, char *str)
{
	char	*content;

	content = ft_substr(ft_strchr(str, '=') + 1, 0,
			ft_strlen(ft_strchr(str, '=') + 1));
	if (content == NULL)
	{
		ft_putstr_fd("error: fatal\n", 2);
		return (1);
	}
	if ((*list)->content)
		free((*list)->content);
	(*list)->content = content;
	if ((*list)->equal == 0)
		(*list)->equal = 1;
	return (0);
}

void	add_elem(int ret, int i, t_env_lst **ptr, char **var)
{
	char	*name;

	name = NULL;
	if (ret == 1)
		name = ft_substr(var[i], 0, ft_whereis_char(var[i], '='));
	else if (ret == 2)
		name = ft_substr(var[i], 0, ft_whereis_char(var[i], '+'));
	else if (ret == 3)
		name = ft_strdup(var[i]);
	find_var(ptr, name);
	if (ft_strcmp((*ptr)->name, name))
	{
		if (ret != 3)
			(*ptr)->next = ft_lstnew_env(name, 1, NULL);
		else
			(*ptr)->next = ft_lstnew_env(name, 0, NULL);
		*ptr = (*ptr)->next;
	}
	if (ret == 1)
		ret = export_add(ptr, var[i]);
	if (ret == 2)
		ret = export_cat(ptr, var[i], NULL, NULL);
	free(name);
	name = NULL;
}

int	export_var(char **var, t_env_lst **envlst)
{
	t_env_lst	*ptr;
	int			i;
	int			ret;

	i = -1;
	while (var[++i])
	{
		ptr = *envlst;
		ret = check_name(var[i]);
		if (ret == 0)
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(var[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			continue ;
		}
		else
		{
			add_elem(ret, i, &ptr, var);
			ptr->visible = 1;
		}
	}
	return (0);
}

int	builtin_export(t_cmd_lst *lst, t_env_lst **envlst)
{
	if (!*lst->args)
		builtin_export_sort(*envlst);
	else
		return (export_var(lst->args, envlst));
	return (0);
}
