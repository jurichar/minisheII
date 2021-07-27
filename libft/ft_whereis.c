/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_whereis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 23:41:25 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/24 23:44:22 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_whereis(const char *s, char *charset)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (s[++i])
	{
		j = -1;
		while (charset[++j])
		{
			if (charset[j] == s[i])
				return (i);
		}
	}
	return (i);
}
