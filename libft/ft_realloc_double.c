/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_double.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:41:01 by lebourre          #+#    #+#             */
/*   Updated: 2021/02/03 10:41:22 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_double(char **str)
{
	char	**new;
	int		i;

	if (!str)
	{
		if (!(new = malloc(sizeof(char *) * 2)))
			return (NULL);
		new[1] = NULL;
		return (new);
	}
	i = 0;
	while (str[i])
		i++;
	if (!(new = malloc(sizeof(char *) * (i + 2))))
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
