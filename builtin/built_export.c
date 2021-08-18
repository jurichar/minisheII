/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:18 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/10 13:56:11 by lebourre         ###   ########.fr       */
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

int	export_cat(t_env_lst **list, char *name, char *content)
{
	t_env_lst	*ptr;
	char		*tmp;

	ptr = *list;
	while (ptr && (ft_strcmp(ptr->name, name) != 0))
		ptr = ptr->next;
	if (ptr == NULL)
		return (1);
	tmp = ptr->content;
	ptr->content = ft_strjoin(ptr->content, content);
	if (ptr->content == NULL)
	{
		free(ptr);
		return (2);
	}
	free(ptr);
	return (0);
}

int		export_var(char **var, t_env_lst **envlst)
{
	t_env_lst	*ptr;
	char		*name;
	char		*content;
	int			i;
	int			ret;

	ptr = *envlst;
	while (ptr->next)
		ptr = ptr->next;
	i = -1;
	while (var[++i])
	{
		ret = check_name(var[i]);
		name = NULL;
		content = NULL;
		printf("ret = %d\n", ret);
		if (ret == 2)
		{
			name = ft_substr(var[i], 0, ft_whereis_char(var[i], '='));
			content = ft_substr(ft_strchr(var[i], '=') + 1, 0, ft_strlen(ft_strchr(var[i], '=') + 1));

			printf("OH\n");
		}
		if (ret == 1)
		{
			if (!name)
				name = ft_substr(var[i], 0, ft_whereis_char(var[i], '='));
			ptr->next = ft_lstnew_env(name, 1, NULL);
			if (!content && ft_strchr(var[i], '=') + 1)
			{
				content = ft_substr(ft_strchr(var[i], '=') + 1, 0, ft_strlen(ft_strchr(var[i], '=') + 1));
				ptr->next->content = ft_strdup(content);
			}
			ptr = ptr->next;
			free(name);
			free(content);
		}
		else if (ret == 3) 
		{
			name = ft_substr(var[i], 0, ft_whereis_char(var[i], '='));
			ptr->next = ft_lstnew_env(name, 0, NULL);
			ptr = ptr->next;
		}
	}
	return (0);
}

int		builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	printf("OH!\n");
	if (!*lst->args)
	{
		builtin_export_sort(envlst);
		return (0);
	}
	else
		return (export_var(lst->args, &envlst));
	return (0);
}