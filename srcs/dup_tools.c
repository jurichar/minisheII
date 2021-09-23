/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:37:54 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/23 17:37:56 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_space_sep(char *s, t_env_lst *env)
{
	int		i;
	int		j;
	int		len;
	int		begin_quote;
	int		quote;
	char	*copy;
	char	*str;

	i = -1;
	quote = 0;
	str = ft_strdup(s);
	str = find_env_var(str, env);
	quote = 0;
	i = -1;
	len = -1;
	while (str[++len])
	{
		if (quote == 0 && (str[len] == '\'' || str[len] == '"'))
			quote = get_to_next_quote(s, len);
		if (!str[quote])
			quote = 0;
		if (quote == 0 && (is_space(str[len]) || is_sep(str[len])))
			break ;
		else if (quote && len == quote && str[len + 1] == ' ')
			break ;
		else if (quote && len == quote)
			quote = 0;
	}
	if (!(copy = malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = -1;
	j = 0;
	quote = 0;
	while (++i < len)
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			begin_quote = i;
			quote = get_to_next_quote(str, i);
		}
		if (!str[quote])
			quote = 0;
		if (quote && (str[i] == '\'' || str[i] == '"') && (i == begin_quote || i == quote))
		{
			if (i == quote)
				quote = 0;
			continue ;
		}
		else
			copy[j++] = str[i];
	}
	copy[j] = '\0';
	return (copy);
}