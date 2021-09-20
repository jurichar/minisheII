/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:48:32 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/09 17:49:05 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_args(char *s, char **args)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (args[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	len = 0;
	i = 1;
	new[0] = s;
	while (args[len])
	{
		new[i] = args[len];
		i++;
		len++;
	}
	new[i] = NULL;
	return (new);
}

char	*get_env_by_name(t_env_lst *envlst, char *name)
{
	if (!envlst)
		return (0);
	while (envlst)
	{
		if (ft_strcmp(envlst->name, name) == 0)
			return (envlst->content);
		envlst = envlst->next;
	}
	return (0);
}
