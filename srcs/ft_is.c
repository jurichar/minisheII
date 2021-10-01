/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:08:34 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/01 15:58:10 by jurichar         ###   ########.fr       */
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
