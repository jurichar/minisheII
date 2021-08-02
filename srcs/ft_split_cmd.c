/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:39:11 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/02 18:00:52 by jurichar         ###   ########.fr       */
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

int		cmd_counter(char *str, char *separator)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
		if (!is_separator(str[i], separator)
		&& (is_separator(str[i + 1], separator) || str[i + 1] == '\0'))
			count++;
	return (count);
}
/*
char	***ft_split_cmd2(char *str, char *separator, t_env_lst *env)
{
	char	***cmds;
	int		cmd_count;
	int		i;
	int		j;

	if (!str || !*str)
		return (NULL);
	cmd_count = cmd_counter(str, separator);
	if (!(cmds = malloc(sizeof(char **) * (cmd_count + 1))))
		return (NULL);
	cmds[cmd_count] = NULL;
	i = -1;
	j = 0;
	while (++i < cmd_count)
	{
		while (is_separator(str[j], separator) && str[j])
			j++;
		cmds[i] = ft_split_args(&str[j], env);
		while (!is_separator(str[j], separator) && str[j])
			j++;
	}
	return (cmds);
}
*/

t_cmd_lst	*ft_split_cmd(char *str, t_env_lst *env)
{
	t_cmd_lst	*lst;
	t_cmd_lst	*lst_begin;
	int			cmd_count;
	int			i;
	int			j;
	char		*buf;

	lst = malloc(sizeof(t_cmd_lst));
	lst_begin = malloc(sizeof(t_cmd_lst));
	if (!str || !*str)
		return (NULL);
	cmd_count = cmd_counter(str, SEP);
	j = -1;
	i = 0;
	lst_begin = NULL;
	while (++j < cmd_count)
	{
		lst = ft_new_cmd_list(NULL);
		if (!lst)
			return (NULL);
		while (str[i] && is_separator(str[i], SEP))
			i++;
		buf = get_cmd(&str[i]);
		ft_split_args(buf, &lst, env);
		while (str[i] && !is_separator(str[i], SEP))
			i++;
		lst->sep = str[i];
		free(buf);
		buf = NULL;
		// printf ("%s\n",lst->cmd);
		if (lst_begin == NULL)
			lst_begin = lst;
		lst = lst->next;
	}
	// if (lst_begin->next != NULL)
	return (lst_begin);
}

void	ft_split_cmd2(t_cmd_lst **lst, char *str, t_env_lst *env, char **envp)
{
	t_cmd_lst	*lst_begin;
	int			cmd_count;
	int			i;
	int			j;
	char		*buf;

	lst_begin = *lst;
	if (!str || !*str)
		return ;
	cmd_count = cmd_counter(str, SEP);
	j = -1;
	i = 0;
	while (++j < cmd_count)
	{
		while (str[i] && is_separator(str[i], SEP))
			i++;
		buf = get_cmd(&str[i]);
		ft_split_args(buf, lst, env);
		while (str[i] && !is_separator(str[i], SEP))
			i++;
		(*lst)->sep = str[i];
		if (ft_strcmp(lst_begin->cmd, "NIL") == 0)
			lst_begin = *lst;
		// printf("cmd = %s", (*lst)->cmd);
		if (j + 1 < cmd_count)
			(*lst)->next = ft_new_cmd_list(envp);
		*lst = (*lst)->next;
	}
	*lst = lst_begin;
}
