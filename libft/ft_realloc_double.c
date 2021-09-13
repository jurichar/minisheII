/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:41:01 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 07:16:50 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_lil_util(char **new)
{
	new = malloc(sizeof(char *) * 2);
	if (!new)
		return (NULL);
	new[1] = NULL;
	return (new);
}

char	**ft_realloc_double(char **str)
{
	char	**new;
	int		i;

	if (!str)
		return (ft_lil_util(new));
	i = 0;
	while (str[i])
		i++;
	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		new[i] = ft_strdup(str[i]);
		free(str[i]);
	}
	new[i + 1] = NULL;
	free(str);
	return (new);
}
