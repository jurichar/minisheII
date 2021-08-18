/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 03:40:31 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/18 01:53:27 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char *s)
{
	char	*cmd;
	int		len;
	int		i;

	len = 0;
	while (s[len] && !is_separator(s[len], SEP))
		len++;
	cmd = malloc(sizeof(char) * (len + 1));
	if (cmd == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		cmd[i] = s[i];
	cmd[i] = '\0';
	return (cmd);
}
