/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/04 19:45:57 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_counter(char *str, int *pipe, int quote)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"'))
			quote = get_to_next_quote(str, i);
		if (quote && i == quote)
			quote = 0;
		if (!is_separator(str, str[i], i)
			&& (is_separator(str, str[i + 1], i + 1) || str[i + 1] == '\0'))
		{
			if (str[i + 1] == '|' && (quote == 0 || i + 1 > quote))
			{
				(*pipe)++;
				count++;
			}
			if (str[i + 1] == '\0')
				count++;
		}
	}
	return (count);
}

void	set_line(char *str, t_cmd_lst **lst, t_env_lst *env, char **envp)
{
	t_set_line	inc;
	t_cmd_lst	*lst_begin;
	char		*buf;

	inc.j = -1;
	inc.i = 0;
	lst_begin = *lst;
	inc.cmd_count = cmd_counter(str, &lst_begin->nb_p, 0);
	while (++inc.j < inc.cmd_count)
	{
		if (is_separator(str, str[inc.i], inc.i))
			inc.i++;
		buf = get_cmd(&str[inc.i]);
		if (str[inc.i])
			ft_split_args(buf, lst, env);
		while (str[inc.i] && !is_separator(str, str[inc.i], inc.i))
			inc.i++;
		(*lst)->sep = str[inc.i];
		if (ft_strcmp(lst_begin->cmd, "NIL") == 0)
			lst_begin = *lst;
		if (inc.j + 1 < inc.cmd_count)
			(*lst)->next = ft_new_cmd_list(envp);
		*lst = (*lst)->next;
	}
	*lst = lst_begin;
}

void	ft_split_cmd(t_cmd_lst **lst, char *str, t_env_lst *env, char **envp)
{
	t_cmd_lst	*lst_begin;
	int			i;

	lst_begin = *lst;
	i = check_redir(str);
	if (i == -1)
	{
		printf("syntax error\n");
		lst_begin->cmd = "NIL";
		return ;
	}
	if (!str || !*str)
		return ;
	set_line(str, lst, env, envp);
}
