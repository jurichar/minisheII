/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env___var___manager___2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:49:51 by jurichar          #+#    #+#             */
/*   Updated: 2021/11/03 15:49:53 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_env_var(char *str, t_env_lst *env, int i, int quote)
{
	char	*s;

	s = ft_strdup(str);
	while (s[++i])
	{
		quote = double_quote_status(quote, i, s);
		if (quote == 0 && s[i] == '\'')
		{
			quote = get_to_next_quote(s, i);
			if (s[quote])
				i = quote;
			else
				quote = 0;
			continue ;
		}
		if (quote == 0 && is_sep(s[i]))
			break ;
		else if (s[i] == '$')
		{
			s = insert_env_var(s, i, env, quote);
			if (!s)
				return (NULL);
			quote = 0;
			i = -1;
		}
	}
	free(str);
	return (s);
}
