/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/11/02 16:12:15 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_the_file(char *arg)
{
	char	*line;
	int		fd;

	fd = open("libft/.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, arg) == 0)
			break ;
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	close (fd);
}

void	find_redir_double(t_cmd_lst *lst)
{
	t_redir	*ptr;

	ptr = lst->redir;
	while (ptr)
	{
		if (ptr->redir == IN_DOUBLE)
			fill_the_file(ptr->arg);
		ptr = ptr->next;
	}
}

void	sigito(int sig)
{
	write(1, "\n", 1);
	exit(130);
}