/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:24:00 by lebourre          #+#    #+#             */
/*   Updated: 2020/11/17 20:25:28 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = -1;
	if (*s2 == '\0' || !s2)
		return ((char*)s1);
	while (s1[++i] && i < len)
	{
		j = 0;
		while (j + i < len && s1[j + i] == s2[j] && s1[j + i])
			j++;
		if (s2[j] == 0)
			return ((char*)&s1[i]);
	}
	return (NULL);
}
