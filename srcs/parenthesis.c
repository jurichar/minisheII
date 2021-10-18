/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:56:18 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/18 14:47:03 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int		check_surroundings(char *s, int pos, char pth)
// {
// 	if (pth == '(')
// 	{
// 		while (--pos >= 0)
// 		{
// 			if ((!is_space(s[pos]) && 
// 		}
// 	}
// }

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

int	check_empty_pth(char *s)
{
	int	i;
	int	quote;
	int	ret;

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
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && s[i] == '(')
			return (ret + check_empty_pth(&s[i]));
		i++;
	}
	return (ret);
}

int	check_back_pth(char *s, int i, int pth_nb)
{
	int	status;
	int	quote;

	status = 0;
	quote = 0;
	while (--i >= 0)
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
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
		return (check_back_pth(s, i, ++pth_nb));
	return (0);
}

int	check_front_pth(char *s, int i, int pth_nb, int inside)
{
	int	status;
	int	quote;

	status = 0;
	quote = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && i == quote)
			quote = 0;
		i += skip_space(&s[i]);
		if (s[i] == '(' && quote == 0 && ((pth_nb == 0 && status == 0)
			|| (inside && status == 0)))
		{
			inside++;
			break ;
		}
		else if (s[i] == '(' && quote == 0 && status == 2)
		{
			inside++;
			break ;
		}
		else if (s[i] == '(' && quote == 0 && inside == 0 && pth_nb && status == 0)
			return (i);
		else if (quote == 0 && s[i] == '(' && status == 1)
		{
			return (i);
		}
		if (quote == 0 && s[i] == '&' && s[i + 1] == '&')
		{
			i++;
			status = 2;
		}	
		else if (quote == 0 && s[i] == '|' && s[i + 1] == '|')
		{
			i++;
			status = 2;
		}
		else if (!is_space(s[i]))
			status = 1;
		if (quote == 0 && s[i] == ')')
			inside--;
	}
	if (s[i])
		return (check_front_pth(s, i, ++pth_nb, inside));
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
	ret = check_back_pth(s, ft_strlen(s), 0);
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

int		check_parenthesis(char *s)
{
	//int	i;
	//int	ret;

	if (check_fist_last_pth(s))
		return (1);
	if (check_empty_pth(get_to_first_pth(s)))
		return (1);
	if (check_unclosed_pth(s))
		return (1);
	return (0);
	// i = -1;
	// while (s[++i])
	// {
	// 	if (s[i] == '(')
	// 	{
	// 		ret = check_surroundings(s, i, '(');
	// 		if (ret == -1)
	// 			return (i);
	// 	}
	// 	else if (s[i] == ')')
	// 	{
	// 		ret = check_surroundings(s, i, ')');
	// 		if (ret == -1)
	// 			return (i);
	// 	}
	// }
}