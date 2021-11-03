/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:20:37 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/26 17:10:49 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_squote(char *str)
{
	char	*copy;

	copy = str;
	str = ft_strjoin(str, "\'");
	free(copy);
	return (str);
}

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
