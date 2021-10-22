/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:50:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/22 15:11:36 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	double_quote_status(int quote, int i, char *s)
{
	if (quote == 0 && s[i] == '"')
		quote = get_to_next_quote(s, i);
	if (!s[quote])
		quote = 0;
	if (quote && i == quote)
		quote = 0;
	return (quote);
}

int	quote_status(int quote, int i, char *s)
{
	if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
		quote = get_to_next_quote(s, i);
	if (!s[quote])
		quote = 0;
	if (quote && i == quote)
		quote = 0;
	return (quote);
}

int	get_to_next_quote(char *s, int i)
{
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
	}
	return (i);
}
