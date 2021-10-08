/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:37:54 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/07 18:23:37 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strdup_sep(char *str)
{
	int		i;
	int		lenght;
	char	*copy;

	lenght = 0;
	while (str[lenght] && !is_separator(str, str[lenght], lenght))
		lenght++;
	copy = malloc(sizeof(char) * lenght + 1);
	if (!copy)
		return (NULL);
	i = -1;
	while (++i < lenght)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

char	*malloc_cmdname(char *s, int *ptr_len)
{
	int		quote;
	char	*cmd;
	int		len;

	len = -1;
	quote = 0;
	while (s[++len])
	{
		if (quote == 0 && (s[len] == '\'' || s[len] == '"'))
			quote = get_to_next_quote(s, len);
		if (!s[quote])
			quote = 0;
		if (quote == 0 && (is_space(s[len]) || is_sep(s[len])))
			break ;
		else if (quote && len == quote && s[len + 1] == ' ')
			break ;
		else if (quote && len == quote)
			quote = 0;
	}
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	*ptr_len = len;
	return (cmd);
}

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
	line = malloc(sizeof(char) * len + 1);
	if (!line)
		return (NULL);
	*ptr_len = len;
	return (line);
}

void	get_line_without_quote(char	*str, char *copy, int len, int quote)
{
	int		i;
	int		j;
	int		begin_quote;

	i = -1;
	j = 0;
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
	get_line_without_quote(str, copy, len, 0);
	free(str);
	return (copy);
}
