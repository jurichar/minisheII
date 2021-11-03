/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:08:34 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/20 13:55:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_separator(char *s, char c, int pos)
{
	int	i;
	int	quote;
	int	type;

	if (c != '|' && c != '&')
		return (0);
	if (s[pos] == '&' && s[pos + 1] != '&')
		return (0);
	if (s[pos] == '|' && s[pos + 1] != '|')
		type = 1;
	else
		type = 2;
	i = -1;
	quote = 0;
	while (s[++i])
	{
		quote = quote_status(quote, i, s);
		if (i == pos && quote == 0)
			return (type);
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
