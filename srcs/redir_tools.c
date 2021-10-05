/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:44:08 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/05 16:44:09 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int     check_redir(char *s)
{
    int i;
    int len;

    len = 0;
    i = -1;
    while (s[++i])
	{
		if (is_redir(s, s[i], i))
			i = skip_redir(s, i);
		if (i == -1)
			return (i);
		len++;
	}
    return (len);
}