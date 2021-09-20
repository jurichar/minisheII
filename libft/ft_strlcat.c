/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:23:45 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 07:00:02 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (ft_strlen(dst) >= size)
		return (len_src + size);
	len = ft_strlen(dst) + len_src;
	while (*dst)
		dst++;
	i = 0;
	while (i < size - 1 - (len - len_src) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}
