/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 12:10:52 by lebourre          #+#    #+#             */
/*   Updated: 2021/07/12 11:28:16 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_whereis_char(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_strjoin_till_space(char const *s1, char const *s2)
{
	char		*new;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	j = -1;
	while (s2[++j] && !is_space(s2[j]))
		new[i++] = s2[j];
	if (i > 0 && (new[i - 1] == '\'' || new[i - 1] == '"'))
		new[i - 1] = '\0';
	new[i] = '\0';
	return (new);
}

int	get_to_next_quote(char *s, int i)
{
	int	end_quote;

	end_quote = 0;
	if (s[i] == '\'')
	{
		i++;
		while (s[i] && s[i] != '\'')
			i++;
	}
	else if (s[i] == '"')
	{
		i++;
		while (s[i] && s[i] != '"')
			i++;
	}
	return (i);
}

int	pass_cmd_name(char *s, int i)
{
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == ' ')
		i++;
	while (s[i] && !((s[i] >= 9 && s[i] <= 13) || s[i] == ' '))
		i++;
	return (i);
}

t_env_lst	*get_env(t_env_lst *list, char **envp)
{
	int			i;
	int			j;
	char		*name;
	char		*content;
	t_env_lst	*begin;

	j = 0;
	while (envp[0][j] != '=')
		j++;
	name = ft_substr(envp[0], 0, j);
	while (envp[0][++j])
		;
	content = ft_substr(ft_strchr(envp[0], '=') + 1, 0, j);
	list = ft_lstnew_env(name, 1, content);
	free(name);
	free(content);
	begin = list;
	i = 0;
	while (envp[++i])
	{
		j = -1;
		while (envp[i][++j] != '=')
			;
		name = ft_substr(envp[i], 0, j);
		while (envp[i][++j])
			;
		content = ft_substr(ft_strchr(envp[i], '=') + 1, 0, j);
		list->next = ft_lstnew_env(name, 1, content);
		free(name);
		free(content);
		list = list->next;
	}
	return (begin);
}
