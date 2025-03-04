/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 17:48:32 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/07 17:45:14 by lebourre         ###   ########.fr       */
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
	new[0] = ft_strdup(s);
	while (args[len])
	{
		new[i] = ft_strdup(args[len]);
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
