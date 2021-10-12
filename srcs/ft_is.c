/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:08:34 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/12 15:37:24 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_separator(char *s, char c, int pos)
{
	int	i;
	int	quote;

	if (c != '|' && c != '&')
		return (0);
	if (s[pos] == '&' && s[pos + 1] != '&')
		return (0);
	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote == 1 && i == quote)
			quote = 0;
		if (i == pos && quote == 0)
			return (1);
	}
	return (0);
}

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

int	is_redir(char *s, char c, int pos)
{
	int	i;
	int	quote;

	if (c != '>' && c != '<')
		return (0);
	i = -1;
	quote = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote == 1 && i == quote)
			quote = 0;
		if (i == pos && quote == 0)
			return (1);
	}
	return (0);
}
