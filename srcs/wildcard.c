/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:27:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/21 14:32:28 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0' && str[i + j + 1] == '\0')
				return (&str[i + 1]);
			if (to_find[j + 1] == WILDC)
				return (&str[i + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}

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
		while ((dir = readdir(d)) != NULL)
		{
			files[i++] = ft_strdup(dir->d_name);
			files = ft_realloc_double(files);
		}
		closedir(d);
	}
	return(files);
}

char	**get_match(char *wd, char **files)
{
	char	**ret_files;
	int		i;
	int		j;
	int		k;
	char	*file;

	i = -1;
	ret_files = ft_realloc_double(NULL);
	k = 0;
	while (files[++i])
	{
		j = 0;
		file = files[i];
		while (wd[j])
		{
			if (j == 0 && wd[j] != WILDC && wd[j] != file[0])
				break ;
			if (wd[j] != WILDC)
			{
				file = ft_strstr(file, &wd[j]);
				if (!file)
					break ;
				while (wd[j + 1] && wd[j + 1] != WILDC)
					j++;
			}
			j++;
			if (wd[j] == '\0')
			{
				ret_files[k++] = ft_strdup(files[i]);
				ret_files = ft_realloc_double(ret_files);
			}
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
	int		quote;

	i = -1;
	quote = 0;
	new = ft_strdup(s);
	while (s[++i])
	{
		if (is_space(s[i]) && quote == 0)
			break ;
		if (s[i] == '"' && quote == 0)
			quote = 1;
		else if (s[i] == '"' && quote == 1)
			quote = 0;
		if (quote == 0 && s[i] == '*')
			new[i] = WILDC;
		else
			new[i] = s[i];
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
	i = 0;
	while (tab[++i])
	{
		tmp = res;
		res = ft_strjoin(res, " ");
		free(tmp);
		tmp = res;
		res = ft_strjoin(res, tab[i]);
		free(tmp);
	}
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
	return (res);
}

char	*find_wildcard(char *s, char *ptr_begin_wd, char *ptr_post_wd, int i)
{
	int		j;
	char	*new;
	char	*wd;
	char	*tmp;

	new = ft_strdup(s);
	while (new[i])
	{
		if (!is_space(new[i]))
		{
			ptr_begin_wd = &new[i];
			while (new[i] && !is_space(new[i]))
			{
				if (new[i] == '"')
					i = get_to_next_quote(new, i);
				if (new[i] == '*' && (i > 0 && new[i - 1] != '\\'))
				{
					wd = wildcard(ptr_begin_wd);
					while (new[i] && !is_space(new[i]))
					{
						if (new[i] == '"')
							i = get_to_next_quote(s, i);
						i++;
					}
					ptr_post_wd = ft_strdup(&new[i]);
					if (wd)
					{
						tmp = ft_substr(new, 0, ptr_begin_wd - new);
						free(new);
						new = ft_calloc(sizeof(char), ft_strlen(tmp) + ft_strlen(wd) + ft_strlen(ptr_post_wd) + 1);
						ft_strncpy(new, tmp, ft_strlen(tmp));
						free(tmp);
						j = ft_strlen(new);
						ft_strncpy(&new[j], wd, ft_strlen(wd));
						free(wd);
						j = ft_strlen(new);
						ft_strncpy(&new[j], ptr_post_wd, ft_strlen(ptr_post_wd));
					}
					free(ptr_post_wd);
				}
				i++;
			}
		}
		else
			i++;
	}
	return (new);
}
