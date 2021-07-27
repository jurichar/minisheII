/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:42:24 by lebourre          #+#    #+#             */
/*   Updated: 2021/04/28 10:54:13 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(char *str, int buffer_size)
{
	char	*new;
	size_t	curr_len;

	curr_len = ft_strlen(str);
	if (!str)
	{
		if (!(new = malloc(sizeof(char) * (buffer_size + 1))))
			return (NULL);
		ft_bzero(new, buffer_size + 1);
		return (new);
	}
	if (!(new = malloc(sizeof(char *) * curr_len + buffer_size + 1)))
		return (NULL);
	ft_memcpy(new, str, curr_len);
	ft_bzero(new + curr_len, buffer_size + 1);
	free(str);
	return (new);
}
