/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:08:34 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/29 19:39:06 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	is_sep(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	is_redir(char *s, int i)
{
	if ((i == 0 && (s[i] == '>' || s[i] == '<'))
		|| (i > 0 && (s[i] == '>' || s[i] == '<')
			&& (s[i - 1] != '\'' || s[i - 1] != '"')))
		return (1);
	return (0);
}
