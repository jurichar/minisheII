/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/18 21:49:04 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_in_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	( void ) lst;
	( void ) envlst;
	return ;
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
	if (lst->redir->redir == 1)
		ft_redir_in(lst);
	else if (lst->redir->redir == 2)
		ft_redir_out(lst);
	else if (lst->redir->redir == 3)
		ft_redir_out_double(lst);
	else if (lst->redir->redir == 4)
		ft_redir_in_double(lst, envlst);
}
