/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdoubledup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:22:08 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/12 14:22:10 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdoubledup(char **tab)
{
	char	**res;
	int		size;
	int		i;

	size = ft_strdoublelen(tab);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	res[i] = NULL;
	return (res);
}
