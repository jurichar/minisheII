/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:21:27 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/20 14:42:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	built_cd_home(t_env_lst **envlst, int ret)
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
		return (-2);
	}
	ret = chdir((*envlst)->content);
	return (ret);
}
