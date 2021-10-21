/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:19 by user42            #+#    #+#             */
/*   Updated: 2021/10/21 16:40:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand_before_exec(t_cmd_lst **lst, t_env_lst *envlst)
{
	char 	*buf;
	int		j;

	j = -1;
	if ((*lst)->args && (*lst)->args[0])
	{
		while ((*lst)->args[++j])
		{
			(*lst)->args[j] = find_env_var((*lst)->args[j], envlst);
			(*lst)->args[j] = find_wildcard((*lst)->args[j], NULL, 0);
			buf = (*lst)->args[j];
			(*lst)->args[j] = ft_strdup_space_sep((*lst)->args[j], 1);
			free(buf);
		}
	}
}