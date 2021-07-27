/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 18:21:42 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/29 21:49:43 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(char *s, int n)
{
	char	*new;
	int		i;

	i = 0;
	if (!(new = malloc(sizeof(char) * n + 1)))
		return (NULL);
	while (s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int		fill_line(char **file_content, char **line)
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

int		manage_return(char **file_content, char **line, int ret, char *buffer)
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

int		get_next_line(int fd, char **line)
{
	static char *file_content;
	char		*buff;
	char		*tmp;
	int			ret;

	if (!(buff = malloc(sizeof(char) * (4096 + 1)))
	|| fd < 0 || !line || 4096 <= 0)
		return (-1);
	while ((ret = read(fd, buff, 4096)) > 0)
	{
		buff[ret] = '\0';
		if (file_content == NULL)
			file_content = ft_strdup(buff);
		else
		{
			tmp = ft_strjoin(file_content, buff);
			if (tmp == NULL)
				return (-1);
			free(file_content);
			file_content = tmp;
		}
		if (ft_strchr(file_content, '\n'))
			break ;
	}
	return (manage_return(&file_content, line, ret, buff));
}
