/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 16:37:19 by user42            #+#    #+#             */
/*   Updated: 2021/10/26 18:15:55 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**expanded_tab(char **dest, char **srcs, int j)
{
	char	**new;
	int		i;
	int		i2;

	new = malloc(sizeof(char *) * (ft_strdoublelen(dest)
				+ ft_strdoublelen(srcs) + 1));
	i = 0;
	while (i < j)
	{
		new[i] = ft_strdup(dest[i]);
		i++;
	}
	i2 = 0;
	while (srcs[i2])
		new[i++] = ft_strdup(srcs[i2++]);
	i2 = i - (i2 - 1);
	while (dest[i2])
		new[i++] = ft_strdup(dest[i2++]);
	new[i] = NULL;
	ft_free_double_char(dest);
	ft_free_double_char(srcs);
	return (new);
}

void	reposition_args(t_cmd_lst **lst)
{
	int	i;

	i = 0;
	while ((*lst)->args[i])
		i++;
	while ((*lst)->args[i + 1])
	{
		free((*lst)->args[i]);
		(*lst)->args[i] = ft_strdup((*lst)->args[i + 1]);
		i++;
	}
	(*lst)->args[i] = NULL;
}

void	expand_check(t_cmd_lst **lst, int j, char *buf)
{
	char	**tab_buf;
	int		size;

	if ((ft_strcmp((*lst)->args[j], buf)) == 0)
				(*lst)->args[j] = ft_strdup_space_sep((*lst)->args[j], 1);
	else
	{
		tab_buf = ft_split((*lst)->args[j], ' ');
		size = ft_strdoublelen(tab_buf);
		(*lst)->args = expanded_tab((*lst)->args, tab_buf, j);
		j += size - 1;
	}
}

void	expand_before_exec(t_cmd_lst **lst, t_env_lst *envlst, int j)
{
	char	*buf;

	if ((*lst)->args && (*lst)->args[0])
	{
		while ((*lst)->args[j])
		{

			(*lst)->args[j] = find_env_var((*lst)->args[j], envlst, -1, 0);
			if ((*lst)->args[j] == NULL)
			{
				reposition_args(lst);
				continue ;
			}
			buf = ft_strdup((*lst)->args[j]);
			(*lst)->args[j] = find_wildcard((*lst)->args[j], NULL, 0,
					ft_strdup((*lst)->args[j]));
			expand_check(lst, j, buf);
			free(buf);
			j++;
		}
	}
}
