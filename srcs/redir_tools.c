/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:08 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/05 16:44:09 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	how_many_redir(char *s)
{
	int		i;
	int		count;
	int		quote;

	i = -1;
	count = 0;
	quote = 0;
	while (s[++i])
	{
		if (quote == 0 && is_sep(s[i]))
			break ;
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && quote == i)
			quote = 0;
		if (quote == 0 && (s[i] == '>' || s[i] == '<'))
		{
			if ((s[i] == '>' && s[i + 1] == '>')
				|| (s[i] == '<' && s[i + 1] == '<'))
				i++;
			count++;
		}
	}
	return (count);
}

int	which_redir(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (IN_DOUBLE);
		else
			return (IN);
	}
	else if (str[0] == '>')
	{
		if (str[1] ==  '>')
			return (OUT_DOUBLE);
		else
			return (OUT);
	}
	else
		return (0);
}

int     check_redir(char *s)
{
    int i;
    int len;

    len = 0;
    i = -1;
    while (s[++i])
	{
		if (is_redir(s, s[i], i))
			i = skip_redir(s, i);
		if (i == -1)
			return (i);
		len++;
	}
    return (len);
}