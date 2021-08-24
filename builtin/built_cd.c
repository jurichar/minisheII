/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:34:38 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/24 21:19:57 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_cd_tild(t_env_lst *envlst)
{
	while (envlst)
	{
		if (ft_strcmp("HOME", envlst->name) == 0)
			break ;
		envlst = envlst->next;
	}
	return (chdir(envlst->content));
}

int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst, int ret)
{
	if (lst->args[0] == NULL)
	{
		while (envlst)
		{
			if (ft_strcmp("HOME", envlst->name) == 0)
				break ;
			envlst = envlst->next;
		}
		if (envlst == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
		ret = chdir(envlst->content);
	}
	else if (ft_strcmp(lst->args[0], "~") == 0)
		ret = builtin_cd_tild(envlst);
	else
		ret = chdir(lst->args[0]);
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", lst->args[0]);
		ret = 1;
	}
	return (ret);
}
