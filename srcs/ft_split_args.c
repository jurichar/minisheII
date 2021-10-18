/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:56:25 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/18 15:25:09 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	args_counter(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	i = pass_cmd_name(str, i);
	while (str[i] && !is_sep(str[i + 1]))
	{
		if (str[i - 1] == ' ' && (str[i] == '\'' || str[i] == '"'))
		{
			i = get_to_next_quote(str, i);
			count++;
		}
		else if (!is_space(str[i])
			&& (is_space(str[i + 1]) || str[i + 1] == '\0'
				|| is_sep(str[i + 1])))
			count++;
		i++;
	}
	return (count);
}

char	*get_cmd_name(char *s, int i, int j, int quote)
{
	int		begin_quote;
	int		len;
	char	*cmd;

	cmd = malloc_cmdname(s, &len);
	while (++i < len)
	{
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
		{
			begin_quote = i;
			quote = get_to_next_quote(s, i);
		}
		if (!s[quote])
			quote = 0;
		if (quote && (s[i] == '\'' || s[i] == '"')
			&& (i == begin_quote || i == quote))
		{
			if (i == quote)
				quote = 0;
		}
		else
			cmd[j++] = s[i];
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*manage_redir(char *str, t_cmd_lst **lst)
{
	char	*tmp;

	if (how_many_redir(str) > 0)
	{
		tmp = get_redir(str, *lst);
		free(str);
		str = tmp;
	}
	return (str);
}

void	set_words(char *str, t_cmd_lst **lst, t_env_lst *env, int j)
{
	int	i;
	int	args_count;

	args_count = args_counter(str);
	i = 0;
	while (++i < args_count && str[j])
	{
		while (str[j] && is_space(str[j]))
			j++;
		(*lst)->args[i - 1] = ft_strdup_space_sep(&str[j], env);
		while (!is_space(str[j]) && str[j])
		{
			if (str[j] == '\'' || str[j] == '"')
				j = get_to_next_quote(str, j);
			j++;
		}
	}
	(*lst)->args[i - 1] = NULL;
	free(str);
}

void	ft_split_args(char *s, t_cmd_lst **lst, t_env_lst *env)
{
	char	*str;
	int		args_count;
	int		j;

	str = clear_parenthesis(s);
	str = find_env_var(str, env);
	str = find_wildcard(str, NULL, 0);
	str = manage_redir(str, lst);
	args_count = args_counter(str);
	(*lst)->args = malloc(sizeof(char *) * (args_count + 1));
	j = 0;
	while (is_space(str[j]) && str[j])
		j++;
	(*lst)->cmd = get_cmd_name(&str[j], -1, 0, 0);
	while (!is_space(str[j]) && str[j])
		j++;
	set_words(str, lst, env, j);
}
