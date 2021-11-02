/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/11/02 16:51:47 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_redir_in_double(t_cmd_lst *lst)
{
	lst->fd[0] = open("libft/.tmp", O_RDONLY, 0666);
	if (lst->fd[0] == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->redir->arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	dup2(lst->fd[0], 0);
	return (1);
}

void	ft_redir_out_double(t_cmd_lst *lst)
{
	lst->fd[1] = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0666);
	dup2(lst->fd[1], 1);
}

void	ft_redir_out(t_cmd_lst *lst)
{
	char	*file;

	file = lst->redir->arg;
	lst->fd[1] = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(lst->fd[1], 1);
	close(lst->fd[1]);
}

int	ft_redir_in(t_cmd_lst *lst)
{
	lst->fd[0] = open(lst->redir->arg, O_RDONLY, 0666);
	if (lst->fd[0] == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->redir->arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	else
	{
		dup2(lst->fd[0], 0);
		close(lst->fd[0]);
		return (1);
	}
}

int	ft_redir(t_cmd_lst *lst, t_env_lst *envlst, int x)
{
	int	i;

	i = TRUE;
	if (x == 0)
		find_redir_double(lst);
	if (lst->redir->redir == OUT)
		ft_redir_out(lst);
	else if (lst->redir->redir == OUT_DOUBLE)
		ft_redir_out_double(lst);
	else if (lst->redir->redir == IN)
		i = ft_redir_in(lst);
	else if (lst->redir->redir == IN_DOUBLE)
		i = ft_redir_in_double(lst);
	if (lst->redir->next)
	{
		lst->redir = lst->redir->next;
		ft_redir(lst, envlst, 1);
	}
	return (i);
}
