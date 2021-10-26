/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:08 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/22 19:51:52 by lebourre         ###   ########.fr       */
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
	if (lst->args[0] && lst->args[1])
	{
		printf("exit\n");
		printf("minishell: exit: too many arguments\n");
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (lst->args[0] && check_exit_error(lst))
	{
		printf("exit\n");
		printf("minishell: exit: %s: numeric argument required\n", lst->args[0]);
		g_exit_code = 255;
	}
	else if (lst->args[0])
	{
		printf("exit\n");
		g_exit_code = ft_atoi(lst->args[0]) % 256;
	}
	else
		printf("exit\n");
	ft_free_env(envlst);
	ft_free_double_char(lst->envp);
	exit(g_exit_code);
	return (g_exit_code);
}
