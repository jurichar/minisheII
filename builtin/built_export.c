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
	if (valid_identifier(*s, 1))
		return (1);
	s++;
	while (*s && *s != '+' && *s != '=')
	{
		if (valid_identifier(*s, 2))
			return (1);
		s++;
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

	var = lst->args;
	while (envlst->next)
		envlst = envlst->next;
	i = -1;
	while (var[++i])
	{
		j = 0;
		if (check_name(var[i]))
		{
			i++;
		}
		else
		{
			if (var[i][j] == '\0' || var[i][j])
			{		

			}
			name = ft_substr(var[i], 0, j);
			while (var[i][j])
				j++;
			content = ft_substr(ft_strchr(var[i], '=') + 1, 0, j);
			envlst->next = ft_lstnew_env(name, 1, content);
			free(name);
			free(content);
			envlst = envlst->next;
		}
	}
	return (0);
}

int		builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (!*lst->args)
	{
		builtin_export_sort(envlst);
		return (0);
	}
	else
		return (export_var(lst, envlst));
	return (0);
}