/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:18 by jurichar          #+#    #+#             */
/*   Updated: 2021/09/13 06:46:37 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	valid_identifier(char c, int pos)
{
	if (pos == 1 && (c == '_' || (ft_isalpha(c))))
		return (1);
	else if (pos == 2 && (c == '_' || (ft_isalnum(c))))
		return (1);
	return (0);
}

int	check_name(char *s)
{
	if (!valid_identifier(*s, 1))
		return (0);
	s++;
	while (*s && *s != '+' && *s != '=')
	{
		if (!valid_identifier(*s, 2))
			return (0);
		s++;
	}
	if (*s == '=')
		return (1);
	else if (*s == '+')
		return (2);
	else if (!*s)
		return (3);
	return (0);
}

void	find_var(t_env_lst **ptr, char *name)
{
	while ((*ptr)->next && (ft_strcmp((*ptr)->name, name) != 0))
		*ptr = (*ptr)->next;
}

int	export_cat(t_env_lst **list, char *str)
{
	char		*tmp;
	char		*content;

	content = ft_substr(ft_strchr(str, '=') + 1, 0,
			ft_strlen(ft_strchr(str, '=') + 1));
	if (content == NULL)
	{
		printf("error: fatal\n");
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
		printf("error: fatal\n");
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
		printf("error: fatal\n");
		return (1);
	}
	if ((*list)->content)
		free((*list)->content);
	(*list)->content = content;
	if ((*list)->equal == 0)
		(*list)->equal = 1;
	return (0);
}

int	export_var(char **var, t_env_lst **envlst)
{
	t_env_lst	*ptr;
	char		*name;
	int			i;
	int			ret;

	i = -1;
	while (var[++i])
	{
		ptr = *envlst;
		ret = check_name(var[i]);
		if (ret == 0)
			continue ;
		if (ret == 1)
			name = ft_substr(var[i], 0, ft_whereis_char(var[i], '='));
		else if (ret == 2)
			name = ft_substr(var[i], 0, ft_whereis_char(var[i], '+'));
		else if (ret == 3)
			name = ft_strdup(var[i]);
		find_var(&ptr, name);
		if (ft_strcmp(ptr->name, name))
		{
			printf("addr->next == %p\n", ptr->next);
			if (ret != 3)
			{
				printf("HELLO\n");
				ptr->next = ft_lstnew_env(name, 1, NULL);
			}	
			else
			{
				printf("OLLEH\n");
				ptr->next = ft_lstnew_env(name, 0, NULL);
			}
			printf("coucou\n");
			ptr = ptr->next;
		}
		if (ret == 1)
			ret = export_add(&ptr, var[i]);
		if (ret == 2)
			ret = export_cat(&ptr, var[i]);	
		free(name);
	}
	return (0);
}

int		builtin_export(t_cmd_lst *lst, t_env_lst **envlst)
{
	if (!*lst->args)
		builtin_export_sort(*envlst);
	else
		return (export_var(lst->args, envlst));
	return (0);
}