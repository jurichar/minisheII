/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:08 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/18 16:39:00 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_exit(t_cmd_lst *lst)
{
	int	i;

	i = 0;
	if (lst->args[0] && lst->args[1])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return (g_exit_code);
	}
	while (lst->args[0][i] && ft_isdigit(lst->args[0][i]))
		i++;
	if (lst->args[0][i])
	{
		printf("minishell: exit: %s: numeric argument required\n", lst->args[0]);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (lst->args[0])
		g_exit_code = ft_atoi(lst->args[0]) % 256;
	printf("exit\n");
	exit(g_exit_code);
	return (g_exit_code);
}
