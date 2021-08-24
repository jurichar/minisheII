/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 14:12:29 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/24 22:53:41 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		historic_size(void)
{
	int		fd;
	int		line;
	char	buf;

	line = 0;
	fd = open("./historic", O_RDONLY);
	if (fd >= 0)
	{
		while ((read(fd, &buf, 1)) != 0)
		if (buf == '\n')
			line++;
	}
	close(fd);
	return (line);
}

char	*get_historic(int up)
{
	int		i;
	int		fd;
	char	**line;
	char	*res;

	fd = open("./historic", O_RDONLY);
	line = malloc(sizeof(char *) * 2);
	line[0] = NULL;
	line[1] = NULL;
	i = -1;
	if (fd >= 0)
	{
		while ((get_next_line(fd, &line[++i])) == 1)
			line = ft_realloc_double(line);
		while (i > 0 && up > 0)
		{
			i--;
		up--;
		}
		res = ft_strdup(line[i]);
		i = -1;
		while (line[++i])
			free(line[i]);
	}
	else
	{
		res = malloc(sizeof(char) + 1);
		res = ft_strdup("");
	}
	// free(line);
	close(fd);
	return (res);
}
