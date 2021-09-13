/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 18:23:40 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 07:50:18 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*new;
	int		len;
	int		i;

	len = ft_strlen(s);
	new = malloc (sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = s[i];
	new[i] = '\0';
	return (new);
}
