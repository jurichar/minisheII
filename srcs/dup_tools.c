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

char	*malloc_line(char *str, int *ptr_len)
{
	int		quote;
	char	*line;
	int		len;

	quote = 0;
	len = -1;
	while (str[++len])
	{
		if (quote == 0 && (str[len] == '\'' || str[len] == '"'))
			quote = get_to_next_quote(str, len);
		if (!str[quote])
			quote = 0;
		if (quote == 0 && (is_space(str[len]) || is_sep(str[len])))
			break ;
		else if (quote && len == quote && str[len + 1] == ' ')
			break ;
		else if (quote && len == quote)
			quote = 0;
	}
	if (!(line = malloc(sizeof(char) * len + 1)))
		return (NULL);
	*ptr_len = len;
	return (line);
}

void	get_line_without_quote(char	*str, char *copy, int len)
{
	int		i;
	int		j;
	int		begin_quote;
	int		quote;

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
		if (quote && (str[i] == '\'' || str[i] == '"')
			&& (i == begin_quote || i == quote))
		{
			if (i == quote)
				quote = 0;
		}
		else
			copy[j++] = str[i];
	}
	copy[j] = '\0';
}

char	*ft_strdup_space_sep(char *s, t_env_lst *env)
{
	char	*copy;
	char	*str;
	int		len;

	str = ft_strdup(s);
	str = find_env_var(str, env);
	copy = malloc_line(str, &len);
	get_line_without_quote(str, copy, len);
	return (copy);
}