/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:22:56 by lebourre          #+#    #+#             */
/*   Updated: 2020/11/17 18:15:08 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	if (!dst && !src)
		return (NULL);
	ptr = (unsigned char *)dst;
	i = -1;
	while (++i < n)
	{
		*ptr = *(unsigned char *)src;
		ptr++;
		src++;
	}
	return (dst);
}
