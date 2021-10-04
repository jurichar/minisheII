/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:21:42 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/17 16:41:20 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *s, int n)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(sizeof(char) * n + 1);
	if (new == NULL)
		return (NULL);
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	fill_line(char **file_content, char **line)
{
	int		len;
	char	*tmp;

	len = 0;
	while ((*file_content)[len] && (*file_content)[len] != '\n')
		len++;
	if ((*file_content)[len] == '\n')
	{
		*line = ft_strndup(*file_content, len);
		tmp = ft_strdup(&(*file_content)[len + 1]);
		if (tmp == NULL)
			return (-1);
		free(*file_content);
		*file_content = tmp;
	}
	else
	{
		*line = ft_strdup(*file_content);
		if (*line == NULL)
			return (-1);
		free(*file_content);
		*file_content = NULL;
	}
	return (1);
}

int	manage_return(char **file_content, char **line, int ret, char *buffer)
{
	free(buffer);
	if (ret < 0)
		return (-1);
	else if (ret == 0 && *file_content == NULL)
	{
		*line = ft_strdup("");
		if (*line == NULL)
			return (-1);
		return (0);
	}
	else
	{
		if (fill_line(&(*file_content), line) == -1)
			return (-1);
		if (*file_content == NULL)
			return (0);
		return (1);
	}
}

char	*cat_content(char *file_content, char *buff)
{
	char	*tmp;

	tmp = ft_strjoin(file_content, buff);
	if (tmp == NULL)
	{
		free(file_content);
		return (NULL);
	}
	free(file_content);
	file_content = tmp;
	return (file_content);
}

int	get_next_line(int fd, char **line)
{
	static char	*file_content;
	char		*buff;
	int			ret;

	buff = malloc(sizeof(char) * 4096 + 1);
	if (buff == NULL || !line || fd < 0)
		return (-1);
	ret = read(fd, buff, 4096);
	while (ret > 0)
	{
		buff[ret] = '\0';
		if (file_content == NULL)
			file_content = ft_strdup(buff);
		else
		{
			file_content = cat_content(file_content, buff);
			if (file_content == NULL)
				return (-1);
		}
		if (ft_strchr(file_content, '\n'))
			break ;
		ret = read(fd, buff, 4096);
	}
	return (manage_return(&file_content, line, ret, buff));
}
