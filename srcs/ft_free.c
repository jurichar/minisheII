/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:07:47 by user42            #+#    #+#             */
/*   Updated: 2021/10/21 14:33:28 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_redir(t_redir *lst)
{
	t_redir	*ptr;

	while (lst)
	{
		free(lst->arg);
		ptr = lst->next;
		free(lst);
		lst = ptr;
	}
}

void	ft_free_cmd(t_cmd_lst *lst)
{
	t_cmd_lst	*ptr;

	if (lst && lst->redir)
		ft_free_redir(lst->redir);
	while (lst)
	{
		if (lst->cmd && (ft_strcmp("NIL", lst->cmd)) != 0)
			free(lst->cmd);
		if (lst->args)
			ft_free_double_char(lst->args);
		ptr = lst->next;
		free(lst);
		lst = ptr;
	}
}

void	ft_free_env(t_env_lst *lst)
{
	t_env_lst	*ptr;

	while (lst)
	{
		free(lst->name);
		free(lst->content);
		ptr = lst->next;
		free(lst);
		lst = ptr;
	}
}