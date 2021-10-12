/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:21:06 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/12 14:21:12 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_env_size(t_env_lst *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		if (lst->equal == 1)
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**update_envp(t_env_lst *lst, int size_env)
{
	char	**new;
	char	*buffer;
	int		i;

	new = malloc(sizeof(char *) * (size_env + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->equal)
		{
			new[i] = ft_strjoin(lst->name, "=");
			if (lst->content)
			{
				buffer = new[i];
				new[i] = ft_strjoin(new[i], lst->content);
				free(buffer);
			}
			i++;
		}
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}
