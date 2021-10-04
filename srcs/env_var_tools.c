/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:20:37 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/04 19:30:01 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*set_start(char *s, int *quote)
{
	*quote = 0;
	if (s[0] == '"')
	{
		*quote = get_to_next_quote(s, 0);
		if (!s[*quote])
			*quote = 0;
		else
			s++;
	}
	s++;
	return (s);
}

char	*get_ret_value(char *ret, char *s, int quote, int len)
{
	char	*tmp;

	tmp = ret;
	ret = ft_strjoin(ft_itoa(g_exit_code), &s[len]);
	free(tmp);
	if (quote == 1)
	{
		tmp = ret;
		ret = ft_strjoin("\"", tmp);
		free (tmp);
	}
	return (ret);
}
