/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:34:38 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/26 15:45:01 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_invisible_pwd(t_env_lst **lst)
{
	t_env_lst	*pwd;
	char		*buf;

	pwd = *lst;
	while (pwd->next)
		pwd = pwd->next;
	buf = malloc(sizeof(char) * 100);
	buf = getcwd(buf, 100);
	pwd->next = ft_lstnew_env("PWD", 1, buf);
	free(buf);
	pwd->next->visible = 0;
}

void	change_data(t_env_lst **old_ptr, t_env_lst **pwd_ptr, t_env_lst **lst)
{
	t_env_lst	*lst_pwd;
	t_env_lst	*lst_oldpwd;
	char		*buf;

	lst_oldpwd = *old_ptr;
	lst_pwd = *pwd_ptr;
	if (lst_pwd)
	{
		if (lst_oldpwd)
			lst_oldpwd->content = ft_strdup(lst_pwd->content);
		buf = malloc(sizeof(char) * 100);
		buf = getcwd(buf, 100);
		lst_pwd->content = buf;
	}
	else if (lst_oldpwd && !lst_pwd)
	{
		if (lst_oldpwd->content)
		{
			free(lst_oldpwd->content);
			lst_oldpwd->content = NULL;
		}
		add_invisible_pwd(lst);
	}
}

void	update_oldpwd(t_env_lst **lst)
{
	t_env_lst	*lst_oldpwd;
	t_env_lst	*lst_pwd;

	lst_oldpwd = *lst;
	lst_pwd = *lst;
	while (lst_oldpwd)
	{
		if (ft_strcmp(lst_oldpwd->name, "OLDPWD") == 0)
			break ;
		lst_oldpwd = lst_oldpwd->next;
	}
	while (lst_pwd)
	{
		if (ft_strcmp(lst_pwd->name, "PWD") == 0)
			break ;
		lst_pwd = lst_pwd->next;
	}
	if (lst_oldpwd)
	{
		lst_oldpwd->visible = 1;
		free(lst_oldpwd->content);
		lst_oldpwd->content = NULL;
	}	
	change_data(&lst_oldpwd, &lst_pwd, lst);
}

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
		ret = built_cd_home(*envlst, ret);
	else if (ft_strcmp(lst->args[0], "~") == 0)
		ret = chdir(getenv("HOME"));
	else
		ret = chdir(lst->args[0]);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(lst->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ret = 1;
	}
	if (ret != -2)
		update_oldpwd(envlst);
	if (ret == -2)
		ret = 1;
	return (ret);
}
