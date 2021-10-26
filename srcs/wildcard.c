/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:27:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/26 15:02:04 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_files(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**files;
	int				i;

	d = opendir(".");
	files = NULL;
	i = 0;
	if (d)
	{
		files = ft_realloc_double(files);
		while (1)
		{
			dir = readdir(d);
			if (dir == NULL)
				break ;
			files[i++] = ft_strdup(dir->d_name);
			files = ft_realloc_double(files);
		}
		closedir(d);
	}
	return (files);
}

char	**get_match(char *wd, char **files)
{
	char	**ret_files;
	int		i;
	int		k;
	char	*file;

	i = -1;
	ret_files = ft_realloc_double(NULL);
	k = 0;
	while (files[++i])
	{
		file = files[i];
		if (check_match(file, wd) && file[0] != '.')
		{
			ret_files[k++] = ft_strdup(files[i]);
			ret_files = ft_realloc_double(ret_files);
		}
	}
	i = -1;
	while (files[++i])
		free(files[i]);
	free(files);
	return (ret_files);
}

char	*set_wildc(char *s)
{
	char	*new;
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = 0;
	quote = 0;
	new = malloc(sizeof(char) * (ft_strlen(s) + 1));
	while (s[++i])
	{
		if (is_space(s[i]) && quote == 0)
			break ;
		if (s[i] == '"' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 1)
			quote = 0;
		if (quote == 0 && s[i] == '*')
			new[j++] = WILDC;
		else if (s[i] != '\'' && s[i] != '"')
			new[j++] = s[i];
	}
	new[i] = '\0';
	new = ft_realloc(new, ft_strlen(new));
	return (new);
}

char	*wildcard(char *to_find)
{
	char	**tab;
	char	*res;
	char	*tmp;
	int		i;

	tmp = set_wildc(to_find);
	tab = get_match(tmp, get_files());
	free(tmp);
	if (tab[0])
		res = ft_strdup(tab[0]);
	else
	{
		free(tab);
		return (NULL);
	}
	res = join_words(tab, res);
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (res);
}

char	*find_wildcard(char *s, char *ptr_begin_wd, int i)
{
	char	*new;

	new = ft_strdup(s);
	while (new[i])
	{
		if (!is_space(new[i]))
		{
			ptr_begin_wd = &new[i];
			while (new[i] && !is_space(new[i]))
			{
				if (new[i] == '"' || new[i] == '\'')
					i = get_to_next_quote(new, i);
				if (new[i] == '*')
					new = wildcard_found(new, ptr_begin_wd, i);
				i++;
			}
		}
		else
			i++;
	}
	free(s);
	return (new);
}
