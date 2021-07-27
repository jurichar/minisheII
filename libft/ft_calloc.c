/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:21:37 by lebourre          #+#    #+#             */
/*   Updated: 2020/11/18 14:33:12 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t data_ammount, size_t size)
{
	char *new;

	if (!(new = malloc(data_ammount * size)))
		return (NULL);
	ft_memset(new, 0, data_ammount * size);
	return (new);
}
