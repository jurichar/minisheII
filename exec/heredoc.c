/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/11/02 17:12:23 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_the_file(char *arg, t_env_lst *envlst)
{
	char	*line;
	int		fd;

	signal(SIGINT, SIG_IGN);
	fd = open("libft/.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, arg) == 0)
			break ;
		line = ft_strdup(line);
		line = find_env_var(line, envlst, -1, 0);
		if (line)
			ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	signal (SIGINT, sig_handler);
	close (fd);
}

void	find_redir_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_redir	*ptr;

	ptr = lst->redir;
	while (ptr)
	{
		if (ptr->redir == IN_DOUBLE)
			fill_the_file(ptr->arg, envlst);
		ptr = ptr->next;
	}
}
