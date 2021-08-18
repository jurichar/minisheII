/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:23:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/03 17:00:12 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

 
t_env_lst		*ft_lstnew_env(char *v_name, int equal, char *v_content)
{
	t_env_lst *new;

	if (!(new = malloc(sizeof(t_env_lst))))
		return (NULL);
	new->name = ft_strdup(v_name);
	new->equal = equal;
	if (equal)
		new->content = ft_strdup(v_content);
	else
		new->content = NULL;
	new->next = NULL;
	return (new);
}
