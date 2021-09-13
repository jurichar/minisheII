/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 14:27:19 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/13 05:57:52 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	get_to_cur_pos(int from, int to)
{
	while (--from >= to)
		ft_putchar_fd('\b', 1);
}

char	*del_char(char *src, int pos)
{
	char	*res;
	int		i;

	res = malloc(sizeof(char) * ft_strlen(src));
	if (res == NULL)
		return (NULL);
	i = -1;
	while (++i < pos - 1)
		res[i] = src[i];
	while (src[++i])
		res[i - 1] = src[i];
	res[i - 1] = '\0';
	free(src);
	return (res);
}

void	clear_and_print(int len, char *s, int pos)
{
	int	tmp;

	tmp = pos;
	while (++tmp < len)
		ft_putstr_fd("\e[1C", 1);
	while (--tmp != 0)
		ft_putstr_fd("\b \b", 1);
	ft_putstr_fd(s, 1);
}

char	*insert_char(char *start, char c, char *end)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(start) + 1 + ft_strlen(end) + 1));
	i = -1;
	while (start[++i])
		res[i] = start[i];
	res[i] = c;
	j = -1;
	while (end[++j])
		res[i++] = end[j];
	res[i] = '\0';
	free(start);
	free(end);
	return (res);
}
