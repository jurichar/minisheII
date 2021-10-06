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

int	check_match(char *file, char *wd)
{
	int	j;

	j = 0;
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
			return (1);
	}
	return (0);
}

char	*insert_match(char *new, char *ptr_begin_wd,
			char *ptr_post_wd, char *wd)
{
	char	*tmp;
	int		j;

	tmp = ft_substr(new, 0, ptr_begin_wd - new);
	free(new);
	new = ft_calloc(sizeof(char), ft_strlen(tmp)
			+ ft_strlen(wd) + ft_strlen(ptr_post_wd) + 1);
	ft_strncpy(new, tmp, ft_strlen(tmp));
	free(tmp);
	j = ft_strlen(new);
	ft_strncpy(&new[j], wd, ft_strlen(wd));
	free(wd);
	j = ft_strlen(new);
	ft_strncpy(&new[j], ptr_post_wd, ft_strlen(ptr_post_wd));
	return (new);
}

char	*join_words(char **tab, char *res)
{
	char	*tmp;
	int		i;

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
	return (res);
}

char	*wildcard_found(char *new, char *ptr_begin_wd, int i)
{
	char	*wd;
	char	*ptr_post_wd;

	wd = wildcard(ptr_begin_wd);
	while (new[i] && !is_space(new[i]))
	{
		if (new[i] == '"' || new[i] == '\'')
			i = get_to_next_quote(new, i);
		i++;
	}
	ptr_post_wd = ft_strdup(&new[i]);
	if (wd)
		insert_match(new, ptr_begin_wd, ptr_post_wd, wd);
	free(ptr_post_wd);
	return (new);
}
