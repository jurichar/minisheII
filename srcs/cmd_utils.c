/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 03:40:31 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 03:41:57 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd(char *s)
{
	char	*cmd;
	int		len;
	int		i;
	int		quote;

	quote = 0;
	len = 0;
	while (s[len] && !is_separator(s, s[len], len))
	{
		if (quote = 0 (s[len] == '"' || s[len] == '\''))
		{
			quote = get_
		}
		len++;
	}	
	cmd = malloc(sizeof(char) * (len + 1));
	if (cmd == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		cmd[i] = s[i];
	cmd[i] = '\0';
	return (cmd);
}
