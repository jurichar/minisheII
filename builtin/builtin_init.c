/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 03:04:12 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/06 14:15:51 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_point_char(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

void	init_built_in(char **str)
{
	str[0] = ft_strdup("cd");
	str[1] = ft_strdup("echo");
	str[2] = ft_strdup("pwd");
	str[3] = ft_strdup("export");
	str[4] = ft_strdup("unset");
	str[5] = ft_strdup("env");
	str[6] = ft_strdup("exit");
	str[7] = 0;
}

int	is_built_in(t_cmd_lst *lst)
{
	char	**builtin_list;
	t_tripl	tripl;

	tripl.x = 0;
	tripl.y = 0;
	tripl.z = FALSE;
	builtin_list = malloc((sizeof(char *) * 8));
	if (!builtin_list)
		return (0);
	init_built_in(builtin_list);
	while (tripl.x < 7)
	{
		tripl.y = ft_strcmp(builtin_list[tripl.x], lst->cmd);
		if (tripl.y == FALSE)
		{
			tripl.z = TRUE;
			break ;
		}
		tripl.x++;
	}
	free_point_char(builtin_list);
	return (tripl.z);
}
