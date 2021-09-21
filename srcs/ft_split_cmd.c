/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/18 01:42:02 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		is_separator(char c, char *separator)
{
	int i;

	i = -1;
	while (separator[++i])
		if (separator[i] == c)
			return (1);
	return (0);
}

char	*ft_strdup_sep(char *str, char *separator)
{
	int		i;
	int		lenght;
	char	*copy;

	lenght = 0;
	while (str[lenght] && !is_separator(str[lenght], separator))
		lenght++;
	if (!(copy = malloc(sizeof(char) * lenght + 1)))
		return (NULL);
	i = -1;
	while (++i < lenght)
		copy[i] = str[i];
	copy[i] = '\0';
	return (copy);
}

int		cmd_counter(char *str, char *separator, int *pipe)
{
	int i;
	int count;
	int	quote;

	i = -1;
	count = 0;
	quote = 0;
	while (str[++i])
	{
		if (quote == 0 && (str[i] == '\'' || str[i] == '"')
			quote = get_to_next_quote(str, i);
		if (quote && i == quote)
			quote = 0;
		if (!is_separator(str[i], separator)
		&& (is_separator(str[i + 1], separator) || str[i + 1] == '\0'))
		{
			if (str[i + 1] == '|')
				(*pipe)++;
			count++;
		}
	}
	return (count);
}

void	ft_split_cmd(t_cmd_lst **lst, char *str, t_env_lst *env, char **envp)
{
	t_cmd_lst	*lst_begin;
	int			cmd_count;
	int			i;
	int			j;
	char		*buf;

	lst_begin = *lst;
	if (!str || !*str)
		return ;
	cmd_count = cmd_counter(str, SEP, &lst_begin->nb_p);
	j = -1;
	i = 0;
	while (++j < cmd_count)
	{
		while (str[i] && is_separator(str[i], SEP))
			i++;
		buf = get_cmd(&str[i]);
		if (str[i])
			ft_split_args(buf, lst, env);
		while (str[i] && !is_separator(str[i], SEP))
			i++;
		(*lst)->sep = str[i];
		if (ft_strcmp(lst_begin->cmd, "NIL") == 0)
			lst_begin = *lst;
		if (j + 1 < cmd_count)
			(*lst)->next = ft_new_cmd_list(envp);
		*lst = (*lst)->next;
	}
	*lst = lst_begin;
}
