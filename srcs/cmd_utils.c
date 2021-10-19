/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 03:40:31 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/19 15:17:20 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_var_cmd(t_set_line *var, char *str, t_cmd_lst *lst_begin)
{
	var->j = -1;
	var->i = 0;
	var->phlvl = 0;
	var->cmd_count = cmd_counter(str, &lst_begin->nb_p, 0);
}

int	which_sep(char *str, int i)
{
	if (str[i] == '|' && str[i + 1] == '|')
		return (OR);
	else if (str[i] == '&' && str[i + 1] == '&')
		return (AND);
	return (str[i]);
}

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

char	*clear_parenthesis(char *s)
{
	char	*res;
	int		i;
	int		j;
	int		quote;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	quote = 0;
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && (s[i] == '(' || s[i] == ')'))
			continue ;
		res[j++] = s[i];
	}
	res[j] = '\0';
	free (s);
	return (res);
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
