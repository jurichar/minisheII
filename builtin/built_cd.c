/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:34:38 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/08 14:33:35 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	update_oldpwd(t_env_lst **begin_lst, char *new_pwd)
// {
// 	t_env_lst	*lst_oldpwd;
// 	t_env_lst	*lst_pwd;
// 	char		*buf;

// 	lst_oldpwd = *begin_lst;
// 	lst_pwd = *begin_lst;
// 	while (lst_oldpwd)
// 	{
// 		if (ft_strcmp(lst->name, "OLDPWD") == 0)
// 			break ;
// 		lst_oldpwd = lst_oldpwd->next;
// 	}
// 	while (lst_pwd)
// 	{
// 		if (ft_strcmp(lst->name, "PWD") == 0)
// 			break ;
// 		lst_pwd = lst_pwd->next;
// 	}
// 	if (lst_pwd && lst_oldpwd)
// 	{
// 		lst_oldpwd->content = ft_strdup(lst_pwd->content);
// 		free(lst_pwd->content);
// 		buf = malloc(sizeof(char) * 100);
// 		buf = getcwd(buf, 100);
// 		lst_pwd->content = buf;
// 	}
// 	else if (lst_oldpwd && !lst_pwd)
// 	{
// 		if (lst_oldpwd->content)
// 		{

// 		}
// 	}
// }

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

int	builtin_cd(t_cmd_lst *lst, t_env_lst **envlst, int ret)
{
	if (lst->args[0] == NULL)
	{
		while (*envlst)
		{
			if (ft_strcmp("HOME", (*envlst)->name) == 0)
				break ;
			(*envlst) = (*envlst)->next;
		}
		if (*envlst == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
			return (1);
		}
		ret = chdir((*envlst)->content);
	}
	else if (ft_strcmp(lst->args[0], "~") == 0)
		ret = builtin_cd_tild(*envlst);
	else
		ret = chdir(lst->args[0]);
	if (ret == -1)
	{
		printf("cd: %s: No such file or directory\n", lst->args[0]);
		ret = 1;
	}
//	update_oldpwd(envlst, lst->args[0]);
	return (ret);
}
