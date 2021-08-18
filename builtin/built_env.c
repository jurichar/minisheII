/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:30:03 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/18 01:23:37 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_env(t_env_lst *envlst)
{
	while (envlst)
	{
		printf("%s=%s\n", envlst->name, envlst->content);
		envlst = envlst->next;
	}
	return (0);
}
