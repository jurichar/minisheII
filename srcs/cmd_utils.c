/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 03:40:31 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/12 15:25:15 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd_lst *lst)
{
	t_cmd_lst	*ptr;

	while (lst)
	{
		if (lst->cmd && (ft_strcmp("NIL", lst->cmd)) != 0)
			free(lst->cmd);
		if (lst->args && *lst->args)
			ft_free_double_char(lst->args);
		ptr = lst->next;
		free(lst);
		lst = ptr;
	}
}

char	*get_cmd(char *s)
{
	char	*cmd;
	int		len;
	int		i;

	len = 0;
	while (s[len] && !is_separator(s, s[len], len))
		len++;
	cmd = malloc(sizeof(char) * (len + 2));
	if (cmd == NULL)
		return (NULL);
	i = -1;
	while (++i < len)
		cmd[i] = s[i];
	cmd[i] = '\0';
	return (cmd);
}
