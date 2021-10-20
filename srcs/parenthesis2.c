/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:56:18 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/20 16:42:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_empty_pth(char *s)
{
	int	i;
	int	quote;
	int	ret;

	if (!*s)
		return (0);
	i = skip_space(&s[1]) + 1;
	if (s[i] == ')')
	{
		printf("minishell: syntax error near unexpected token `)'\n");
		return (1);
	}
	quote = 0;
	ret = 0;
	while (s[i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (!s[quote])
			quote = 0;
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && s[i] == '(')
			return (ret + check_empty_pth(&s[i]));
		i++;
	}
	return (ret);
}

int	check_back_pth(char *s, int i, int pth_nb, int status)
{
	int	quote;

	quote = 0;
	while (--i >= 0)
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (!s[quote])
			quote = 0;
		if (quote && i == quote)
			quote = 0;
		if (s[i] == ')' && quote == 0 && (status == 0 || status == 2))
			break ;
		else if (s[i] == ')' && quote == 0 && status == 1)
			return (i);
		if (quote == 0 && s[i] == '&' && s[i + 1] == '&')
			status = 2;
		else if (quote == 0 && s[i] == '|' && s[i + 1] == '|')
			status = 2;
		else if (!is_space(s[i]))
			status = 1;
	}
	if (i > 0)
		return (check_back_pth(s, i, ++pth_nb, 0));
	return (0);
}

void	set_status(int *status, int *i, char *s, int quote)
{
	if (quote == 0 && s[*i] == '&' && s[*i + 1] == '&')
	{
		*i += 1;
		*status = 2;
	}	
	else if (quote == 0 && s[*i] == '|' && s[*i + 1] == '|')
	{
		*i += 1;
		*status = 2;
	}
	else if (!is_space(s[*i]))
		*status = 1;
}

int	check_front_pth(char *s, int i, int pth_nb, int in)
{
	int	status;
	int	qt;

	status = 0;
	qt = 0;
	if (!s || !*s)
		return (0);
	while (s[++i])
	{
		qt = quote_status(qt, i, s);
		i += skip_space(&s[i]);
		if (s[i] == '(' && qt == 0 && ((pth_nb == 0 && status == 0) || (in
					&& status == 0) || (s[i] == '(' && qt == 0 && status == 2)))
		{
			in++;
			break ;
		}
		else if ((s[i] == '(' && qt == 0 && in == 0 && pth_nb
				&& status == 0) || (qt == 0 && s[i] == '(' && status == 1))
			return (i);
		set_status(&status, &i, s, qt);
		if (qt == 0 && s[i] == ')')
			in--;
		if (!s[i])
			break ;
	}
	if (s[i])
		return (check_front_pth(s, i, ++pth_nb, in));
	return (0);
}

int	check_fist_last_pth(char *s)
{
	int	ret;

	if (check_front_pth(s, -1, 0, 0))
	{
		printf("minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	ret = check_back_pth(s, ft_strlen(s), 0, 0);
	if (ret)
	{
		write(1, "minishell: syntax error near unexpected token `",
			ft_strlen("minishell: syntax error near unexpected token `"));
		ret++;
		ret += skip_space(&s[ret]);
		while (s[ret] && !is_space(s[ret]))
			write(1, &s[ret++], 1);
		write(1, "'\n", 2);
		return (1);
	}
	return (0);
}
