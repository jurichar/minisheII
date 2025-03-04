/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:10:52 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/21 17:10:17 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_and_ret(char *to_print, int to_ret)
{
	ft_putstr_fd(to_print, 1);
	return (to_ret);
}

int	ft_whereis_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_till_space(char const *s1, char const *s2)
{
	char		*new;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && !is_space(s2[j]))
		new[i++] = s2[j];
	if (i > 0 && (new[i - 1] == '\'' || new[i - 1] == '"'))
		new[i - 1] = '\0';
	new[i] = '\0';
	return (new);
}

int	pass_cmd_name(char *s, int i)
{
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	return (i);
}

char	*malloc_line(char *str, int *ptr_len)
{
	int		quote;
	char	*line;
	int		len;

	quote = 0;
	len = 0;
	line = NULL;
	if (!str)
		return (NULL);
	while (str[len])
	{
		quote = quote_status(quote, len, str);
		if (quote == 0 && is_sep(str[len]))
			break ;
		else if (quote && len == quote && str[len + 1] == ' ')
			break ;
		len++;
	}
	line = ft_calloc(sizeof(char), len + 1);
	if (!line)
		return (NULL);
	*ptr_len = len;
	return (line);
}
