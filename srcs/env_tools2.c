/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:09:08 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/13 14:12:34 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_oldpwd(t_env_lst **begin)
{
	t_env_lst *lst;

	lst = *begin;
	while (lst && lst->next)
	{
		if ((ft_strcmp(lst->name, "OLDPWD")) == 0)
			break ;
		lst = lst->next;
	}
	if ((ft_strcmp(lst->name, "OLDPWD")) == 0)
		return ;
	lst->next = ft_lstnew_env("OLDPWD", 1, NULL);
	lst->next->visible = 0;
}