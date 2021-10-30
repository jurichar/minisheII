/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/30 10:33:09 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void fill_the_file(t_cmd_lst *lst)
{
	char *line;
	int fd = open("libft/.tmp", O_CREAT | O_RDWR | O_TRUNC, 0666);

	while (1)
	{
		line = readline("> ");
		if (strcmp(line, lst->redir->arg) == 0)
		{
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	close (fd);
}

int	ft_redir_in_double(t_cmd_lst *lst)
{
	int		fd;

	lst->fd[0] = open("libft/.tmp", O_RDONLY, 0666);
	dup2(lst->fd[0], 0);
	return (1);
}

void	find_redir_double(t_cmd_lst *lst)
{
	while (lst->redir)
	{
		if (lst->redir->redir == IN_DOUBLE)
			fill_the_file(lst);
		if (!lst->redir->next)
			break ;
		lst->redir = lst->redir->next;
	}
}

void 	sigito(int sig)
{
	write(1, "\n", 1);
	exit(130);
}

void	ft_redir_out_double(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0666);
	dup2(fd, 1);
}

void	ft_redir_out(t_cmd_lst *lst)
{
	int		fd;
	char	*file;

	file = lst->redir->arg;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(fd, 1);
}

int	ft_redir_in(t_cmd_lst *lst)
{
	int	fd;

	lst->fd[0] = open(lst->redir->arg, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->redir->arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	else
	{
		dup2(lst->fd[0], 0);
		return (1);
	}
}

int	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	int	i;

	i = TRUE;
	// find_redir_double(lst);
	if (lst->redir->redir == OUT)
	{
		ft_redir_out(lst);
		// close(lst->fd[1]);
	}
	else if (lst->redir->redir == OUT_DOUBLE)
	{
		ft_redir_out_double(lst);
		// close(lst->fd[1]);
	}
	else if (lst->redir->redir == IN)
	{
		i = ft_redir_in(lst);
		// close(lst->fd[0]);
	}
	else if (lst->redir->redir == IN_DOUBLE)
	{
		i = ft_redir_in_double(lst);
	}
	if (lst->redir->next)
	{
		close(lst->fd[0]);
		close(lst->fd[1]);
		lst->redir = lst->redir->next;
		ft_redir(lst, envlst);
	}
	// else
	// {
		// close(lst->fd[1]);
		// close(lst->fd[0]);
	// }
	return (i);
}
