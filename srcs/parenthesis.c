/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:56:18 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/21 17:08:19 by lebourre         ###   ########.fr       */
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
		if (!s[quote])
			quote = 0;
		if (quote && i == quote)
			quote = 0;
	}
	return (&s[i]);
}

int	check_unclosed_pth(char *s, int quote, int level)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (!s[quote])
			quote = 0;
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && s[i] == '(')
			level++;
		else if (quote == 0 && s[i] == ')')
			level--;
	}
	if (level)
		return (print_and_ret("minishell: syntax error: unclosed parenthesis\n",
				1));
	return (0);
}

int	check_parenthesis(char *s)
{
	if (check_fist_last_pth(s))
		return (1);
	if (check_empty_pth(get_to_first_pth(s)))
		return (1);
	if (check_unclosed_pth(s, 0, 0))
		return (1);
	return (0);
}
