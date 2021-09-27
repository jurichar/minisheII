/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/09/27 14:10:30 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_in_double(t_cmd_lst *lst)
{
	int		fd0;
	int		fd;
	char	*line;
	int		i;

	line = "";
	fd0 = open(".lol", O_CREAT | O_RDWR | O_TRUNC, 0777);
	i = 0;
	while (ft_strcmp(line, lst->redir->arg) != 0)
	{
		line = readline("> ");
		if (ft_strcmp(line, lst->redir->arg) != 0)
		{
			ft_putstr_fd(line, fd0);
			ft_putstr_fd("\n", fd0);
		}
		i++;
	}
	close(fd0);
	fd = open(".lol", O_RDWR, 0664);
	dup2(fd, 0);
}

void	ft_redir_out_double(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}

void	ft_redir_out(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	ft_redir_in(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (lst->sep == '|')
	{
		pipor(lst, envlst);
	}
	while (lst->redir->next)
	{
		open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
		lst->redir = lst->redir->next;
	}
	if (lst->redir->redir == 1)
		ft_redir_in(lst);
	else if (lst->redir->redir == 2)
		ft_redir_out(lst);
	else if (lst->redir->redir == 3)
		ft_redir_out_double(lst);
	else if (lst->redir->redir == 4)
		ft_redir_in_double(lst);
}