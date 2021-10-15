/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 09:56:18 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/15 11:31:36 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		check_surroundings(char *s, int pos, char pth)
{
	if (pth == '(')
	{
		while (--pos >= 0)
		{
			if ((!is_space(s[pos]) && 
		}
	}
}

int	check_last_pth(char *s)
{
	int	i;
	int	status;

	i = ft_strlen(s);
	status = 0;
	while (--i >= 0)
	{
		if (s[i] == ')' && (status == 0 || status == 2))
			break ;
		else if (s[i] == ')' && status == 1)
			return (i);
		if (s[i] == '&' && s[i + 1] == '&')
			status = 2;
		else if (s[i] == '|' && s[i + 1] == '|')
			status = 2;
		else if (!is_space(s[i]))
			status = 1;		
	}
	return (0);
}

int	check_fist_pth(char *s)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	while (s[++i])
	{
		i = skip_space(&s[i]);
		if (s[i] == '(' && (status == 0 || status == 2))
			break ;
		else if (s[i] == '(' && status == 1)
			return (i);
		if (s[i] == '&' && s[i + 1] == '&')
			status = 2;
		else if (s[i] == '|' && s[i + 1] == '|')
			status = 2;
		else
			status = 1;		
	}
	return (0);
}

int	check_fist_last_pth(char *s)
{
	int	ret;

	ret = check_fist_pth(s);
	if (check)
	{
		printf("minishell: syntax error near unexpected token `('\n");
		return (1);
	}
	if ()
}

int		check_parenthesis(char *s)
{
	int	i;
	int	ret;

	if (check_fist_last_pth(s))
		return (1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '(')
		{
			ret = check_surroundings(s, i, '(');
			if (ret == -1)
				return (i);
		}
		else if (s[i] == ')')
		{
			ret = check_surroundings(s, i, ')');
			if (ret == -1)
				return (i);
		}
	}
}