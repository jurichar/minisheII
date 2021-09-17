/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:22:52 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 07:06:48 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*ptr1;
	const char	*ptr2;
	size_t		i;

	ptr1 = s1;
	ptr2 = s2;
	i = 0;
	if (n <= 0)
		return (0);
	while (ptr1[i] == ptr2[i] && i < n - 1)
		i++;
	return ((unsigned char)ptr1[i] - (unsigned char)ptr2[i]);
}
