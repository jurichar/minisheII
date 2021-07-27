/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:22:00 by lebourre          #+#    #+#             */
/*   Updated: 2020/11/21 23:54:02 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(long nb)
{
	size_t len;

	len = 0;
	if (nb <= 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	long		nbr;
	size_t		len;
	char		*res;

	len = ft_len(n);
	if (!(res = malloc(sizeof(char) * len + 1)))
		return (NULL);
	res[len--] = '\0';
	nbr = n;
	if (n < 0)
	{
		res[0] = '-';
		nbr = (long)n * -1;
	}
	if (nbr == 0)
		res[len] = '0';
	while (nbr > 0)
	{
		res[len--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (res);
}
