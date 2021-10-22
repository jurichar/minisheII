/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:08 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/22 19:25:26 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_exit_error(t_cmd_lst *lst)
{
	int	i;

	i = 0;
	while (lst->args[0] && lst->args[0][i] && ft_isdigit(lst->args[0][i]))
		i++;
	if (lst->args[0][i] == '-')
		i++;
	while (lst->args[0] && lst->args[0][i] && ft_isdigit(lst->args[0][i]))
		i++;
	if (lst->args[0] && lst->args[0][i])
		return (255);
	return (0);
}

int	builtin_exit(t_cmd_lst *lst, t_env_lst *envlst)
{
	int	i;

	i = 0;
	if (lst->args[0] && lst->args[1])
	{
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (check_exit_error(lst))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", lst->args[0]);
		g_exit_code = 255;
	}
	else if (lst->args[0])
		g_exit_code = ft_atoi(lst->args[0]) % 256;
	ft_free_env(envlst);
	printf("exit\n");
	exit(g_exit_code);
	return (g_exit_code);
}
