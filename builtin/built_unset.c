/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:31 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/26 14:57:05 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_cmd_lst *lst, t_env_lst **env)
{
	int	i;
	int	j;

	i = -1;
	while (lst->args[++i])
	{
		j = -1;
		while (lst->args[i][++j])
		{
			if (j == 0 && !valid_identifier(lst->args[i][j], 1))
			{
				ft_putstr_fd("unset:\t`", 2);
				ft_putstr_fd(lst->args[0], 2);
				ft_putstr_fd("': not a valid indentifier\n", 2);
				return (1);
			}
			else if (!valid_identifier(lst->args[i][j], 2))
			{
				ft_putstr_fd("unset:\t`", 2);
				ft_putstr_fd(lst->args[0], 2);
				ft_putstr_fd("': not a valid indentifier\n", 2);
				return (1);
			}
		}
		ft_env_remove_if(env, lst->args[i], &ft_strcmp);
	}
	return (0);
}
