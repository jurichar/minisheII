/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/13 17:09:15 by jurichar         ###   ########.fr       */
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
	fd = open(".lol", O_RDWR, 0666);
	dup2(fd, 0);
}

void	ft_redir_out_double(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0666);
	dup2(fd, 1);
	if (lst->redir->next && lst->redir->next->redir == IN)
	{
		while (lst->redir->next && lst->redir->next->redir == IN)
			lst->redir = lst->redir->next;
		ft_redir_in(lst);
	}
	close(fd);
}

void	ft_redir_out(t_cmd_lst *lst)
{
	int	fd;

	printf ("coucou\n");
	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(fd, 1);
	if (lst->redir->next && lst->redir->next->redir == IN)
	{
		while (lst->redir->next && lst->redir->next->redir == IN)
			lst->redir = lst->redir->next;
		ft_redir_in(lst);
	}
	close(fd);
}

int	ft_redir_in(t_cmd_lst *lst)
{
	int	fd;

	if (access(lst->redir->arg, 0666) == -1)
	{
		printf ("minishell: %s: No such file or directory\n", lst->redir->arg);
		return (0);
	}
	else
	{
		fd = open(lst->redir->arg, O_RDONLY);
		dup2(fd, 0);
		close(fd);
		return (1);
	}
}

int	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	int	i;

	i = TRUE;
	while (lst->redir->next && (lst->redir->redir == OUT
			|| lst->redir->redir == OUT_DOUBLE)
		&& (lst->redir->next->redir == OUT
			|| lst->redir->next->redir == OUT_DOUBLE))
	{
		open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0666);
		lst->redir = lst->redir->next;
	}
	if (lst->redir->redir == OUT)
		ft_redir_out(lst);
	else if (lst->redir->redir == OUT_DOUBLE)
		ft_redir_out_double(lst);
	else if (lst->redir->redir == IN)
		i = ft_redir_in(lst);
	else if (lst->redir->redir == IN_DOUBLE)
		ft_redir_in_double(lst);
	if (lst->sep == '|')
		pipor(lst, envlst);
	unlink(".lol");
	return (i);
}
