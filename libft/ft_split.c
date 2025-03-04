/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:23:30 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 07:03:14 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_split(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

static int	how_many_words(char *str, char c)
{
	int	words;
	int	i;

	words = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c
			&& ((str[i + 1] == c) || str[i + 1] == '\0'))
			words++;
	return (words);
}

static char	*ft_strdup_split(char *str, char c)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * ft_strlen_split(str, c) + 1);
	if (!new)
		return (0);
	i = 0;
	while (str[i] && (str[i] != c))
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	**ft_split(const char *str, char c)
{
	int		i;
	int		j;
	int		words;
	char	**ret;

	i = 0;
	j = -1;
	words = how_many_words((char *)str, c);
	if (!str)
		return (NULL);
	ret = malloc(sizeof(char *) * (words + 1));
	if (!ret)
		return (0);
	while (++j < words)
	{
		while ((str[i] == c) && str[i])
			i++;
		ret[j] = ft_strdup_split((char *)&str[i], c);
		while ((str[i] != c) && str[i])
			i++;
	}
	ret[j] = NULL;
	return (ret);
}
