/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:56:18 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/18 15:53:28 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_to_first_pth(char *s)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (s[++i] && !(quote == 0 && s[i] == '('))
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && i == quote)
			quote = 0;
	}
	return (&s[i]);
}

int	check_unclosed_pth(char *s)
{
	int	i;
	int	quote;
	int	level;

	i = -1;
	quote = 0;
	level = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && s[i] == '(')
			level++;
		else if (quote == 0 && s[i] == ')')
			level--;
	}
	if (level)
	{
		printf("minishell: syntax error: unclosed parenthesis\n");
		return (1);
	}
	return (0);
}

int	check_parenthesis(char *s)
{
	if (check_fist_last_pth(s))
		return (1);
	if (check_empty_pth(get_to_first_pth(s)))
		return (1);
	if (check_unclosed_pth(s))
		return (1);
	return (0);
}
