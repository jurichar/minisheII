/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:23:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/20 16:13:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_lst	*ft_lstnew_env(char *v_name, int equal, char *v_content)
{
	t_env_lst	*new;

	new = malloc(sizeof(t_env_lst));
	if (!new)
		return (NULL);
	new->name = ft_strdup(v_name);
	new->equal = equal;
	if (equal && v_content)
		new->content = ft_strdup(v_content);
	else
		new->content = NULL;
	new->visible = 1;
	new->next = NULL;
	return (new);
}

t_env_lst	*set_first_elem(t_env_lst **list, char **envp)
{
	int			j;
	char		*name;
	char		*content;

	j = 0;
	while (envp[0][j] != '=')
		j++;
	name = ft_substr(envp[0], 0, j);
	while (envp[0][++j])
		;
	content = ft_substr(ft_strchr(envp[0], '=') + 1, 0, j);
	*list = ft_lstnew_env(name, 1, content);
	free(name);
	free(content);
	return (*list);
}

char	*inc_shlvl(char *shlvl)
{
	int	nb;

	nb = ft_atoi(shlvl) + 1;
	free(shlvl);
	return (ft_itoa(nb));
}

t_env_lst	*get_env(t_env_lst *list, char **envp)
{
	int			i;
	int			j;
	char		*name;
	char		*content;
	t_env_lst	*begin;

	begin = set_first_elem(&list, envp);
	i = 0;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] != '=')
			;
		name = ft_substr(envp[i], 0, j);
		j = ft_strlen(envp[i]);
		content = ft_substr(ft_strchr(envp[i], '=') + 1, 0, j);
		if (ft_strcmp(name, "SHLVL") == 0)
			content = inc_shlvl(content);
		list->next = ft_lstnew_env(name, 1, content);
		free(name);
		free(content);
		list = list->next;
	}
	check_oldpwd(&begin);
	return (begin);
}
