/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:31 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/08 17:36:32 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_unset(t_cmd_lst *lst, t_env_lst *env)
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
				printf("unset:\t`%s': not a valid indentifier\n", lst->args[0]);
				return (1);
			}
			else if (!valid_identifier(lst->args[i][j], 2))
			{
				printf("unset:\t`%s': not a valid indentifier\n", lst->args[0]);
				return (1);
			}
		}
		ft_env_remove_if(&env, lst->args[i], &ft_strcmp);
	}
	return (0);
}
