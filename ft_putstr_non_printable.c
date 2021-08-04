/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/13 08:35:34 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/04 22:33:49 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_hex(char c)
{
	char *hex;

	hex = "0123456789abcdef";
	ft_putchar('\\');
	ft_putchar(hex[(unsigned char)c / 16]);
	ft_putchar(hex[(unsigned char)c % 16]);
}

void	ft_putstr_non_printable(char *str)
{
	while (*str)
	{
		if (*str >= ' ' && *str <= '~')
			ft_putchar(*str);
		else
			print_hex(*str);
		str++;
	}
}
