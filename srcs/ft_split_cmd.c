/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/20 14:12:25 by user42           ###   ########.fr       */
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
		quote = quote_status(quote, i, str);
		if (quote == 0 && !is_separator(str, str[i], i)
			&& (is_separator(str, str[i + 1], i + 1) || str[i + 1] == '\0'))
		{
			count++;
			if (str[i + 1] == '|' && (quote == 0 || i + 1 > quote))
				(*pipe)++;
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

	lst_begin = *lst;
	init_var_cmd(&var, str, lst_begin);
	while (++var.j < var.cmd_count)
	{
		if (var.j != 0 && is_separator(str, str[var.i], var.i))
			var.i += is_separator(str, str[var.i], var.i);
		(*lst)->phlvl = find_phlvl(str, var.i);
		buf = get_cmd(&str[var.i]);
		if (str[var.i])
			ft_split_args(buf, lst);
		while (str[var.i] && !is_separator(str, str[var.i], var.i))
			var.i++;
		(*lst)->sep = which_sep(str, var.i);
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
	int	ret;

	ret = 0;
	if (lst->sep == '|' || lst->sep == AND || lst->sep == OR)
	{
		if (!(lst->next))
		{
			printf ("syntax error\n");
			ret = 1;
		}
		else if (ft_strcmp(lst->next->cmd, "") == 0
			|| ft_strcmp(lst->next->cmd, "NIL") == 0)
		{
			printf ("syntax error\n");
			ret = 1;
		}
	}
	return (ret);
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
	free(s);
}
