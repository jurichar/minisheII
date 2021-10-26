/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:37:54 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/22 15:01:08 by lebourre         ###   ########.fr       */
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

void	copy_until_space(char *dest, char *src)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (src[++i])
	{
		if (quote == 0 && (src[i] == '\'' || src[i] == '"'))
			quote = get_to_next_quote(src, i);
		if (!src[quote])
			quote = 0;
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && is_space(src[i]))
			break ;
		dest[i] = src[i];
	}
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

char	*ft_strdup_space_sep(char *s, int quote)
{
	char	*copy;
	char	*str;
	int		len;

	str = ft_strdup(s);
	copy = malloc_line(str, &len);
	if (quote)
	{
		get_line_without_quote(str, copy, len, 0);
		free(s);
	}
	else
		copy_until_space(copy, str);
	free(str);
	return (copy);
}
