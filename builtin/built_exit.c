/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:08 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/26 14:54:08 by lebourre         ###   ########.fr       */
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
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		g_exit_code = 1;
		return (g_exit_code);
	}
	if (lst->args[0] && check_exit_error(lst))
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(lst->args[0], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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
