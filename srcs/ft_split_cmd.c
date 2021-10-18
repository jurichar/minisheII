/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/18 15:49:46 by lebourre         ###   ########.fr       */
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
			else
				count++;
		}
	}
	return (count);
}

int	find_phlvl(char *s, int pos)
{
	int	i;
	int	phlvl;

	phlvl = 0;
	i = skip_space(s);
	while (s[i] && i != pos)
	{
		if (s[i] == '\'' || s[i] == '"')
			i = get_to_next_quote(s, i);
		if (s[i] == '(')
			phlvl++;
		else if (s[i] == ')')
			phlvl--;
		i++;
	}
	return (phlvl);
}

void	set_line(char *str, t_cmd_lst **lst, char **envp)
{
	t_set_line	var;
	t_cmd_lst	*lst_begin;
	char		*buf;

	var.j = -1;
	var.i = 0;
	var.phlvl = 0;
	lst_begin = *lst;
	var.cmd_count = cmd_counter(str, &lst_begin->nb_p, 0);
	while (++var.j < var.cmd_count)
	{
		if (is_separator(str, str[var.i], var.i))
		{
			if ((str[var.i] == '|' && str[var.i + 1] == '|') || str[var.i] == '&')
				var.i++;
			var.i++;
		}
		(*lst)->phlvl = find_phlvl(str, var.i);
		buf = get_cmd(&str[var.i]);
		if (str[var.i])
			ft_split_args(buf, lst);
		while (str[var.i] && !is_separator(str, str[var.i], var.i))
			var.i++;
		if (str[var.i] == '|' && str[var.i + 1] == '|')
			(*lst)->sep = OR;
		else if (str[var.i] == '&' && str[var.i + 1] == '&')
			(*lst)->sep = AND;
		else
			(*lst)->sep = str[var.i];
		(*lst)->sep_phlvl = find_phlvl(str, var.i);
		if (ft_strcmp(lst_begin->cmd, "NIL") == 0)
			lst_begin = *lst;
		if (var.j + 1 < var.cmd_count)
			(*lst)->next = ft_new_cmd_list(envp);
		*lst = (*lst)->next;
	}
	*lst = lst_begin;
}

int	check_cmd(t_cmd_lst *lst)
{
	while (lst)
	{
		if (lst->sep != 0 && !lst->next->cmd)
		{
			printf("caca\n");
		}
		lst = lst->next;
	}
	return (0);
}

void	ft_split_cmd(t_cmd_lst **lst, char *str, char **envp)
{
	t_cmd_lst	*lst_begin;
	char		*s;

	s = ft_strdup(str);
	lst_begin = *lst;
	if (check_parenthesis(s))
	{
		free(s);
		return ;
	}
	if (check_redir(str) == -1)
	{
		printf("syntax error\n");
		g_exit_code = 1;
		lst_begin->cmd = "NIL";
		return ;
	}
	if (!s || !*s)
		return ;
	set_line(s, lst, envp);
	if (check_cmd(lst_begin))
	{
		free(s);
		return ;
	}
	free(s);
}
