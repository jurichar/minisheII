/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 18:44:20 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/27 19:12:08 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	find_var(t_env_lst **ptr, char *name)
{
	while ((*ptr)->next && (ft_strcmp((*ptr)->name, name) != 0))
		*ptr = (*ptr)->next;
}

int	valid_identifier(char c, int pos)
{
	if (pos == 1 && (c == '_' || (ft_isalpha(c))))
		return (1);
	else if (pos == 2 && (c == '_' || (ft_isalnum(c))))
		return (1);
	return (0);
}

int	check_name(char *s)
{
	if (!valid_identifier(*s, 1))
		return (0);
	s++;
	while (*s && *s != '+' && *s != '=')
	{
		if (!valid_identifier(*s, 2))
			return (0);
		s++;
	}
	if (*s == '=')
		return (1);
	else if (*s == '+')
		return (2);
	else if (!*s)
		return (3);
	return (0);
}
