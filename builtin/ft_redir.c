/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/12 19:31:26 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_in_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	int		i;
	// int		fd;
	// char	*line;
	// fd = open(".tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// dup2(lst->fd[1], 1);
	// while (42)
	// {
	// 	line = readline("> ");
	// 	if (ft_strcmp(lst->redir->arg, line) == 0)
	// 	{
	// 		free(line);
	// 		break;
	// 	}
	// 	write (fd, line, ft_strlen(line));
	// 	free(line);
	// }
	// close(fd);
}




















void	ft_redir_out_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	int fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(fd, 1);
	close(fd);
}

void	ft_redir_out(t_cmd_lst *lst, t_env_lst *envlst)
{
	int fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(fd, 1);
	close(fd);
}

void	ft_redir_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	int fd = open(lst->redir->arg, O_RDONLY);
	dup2(fd, 0);
	close(fd);
}

void	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (lst->redir->redir == 1)
		ft_redir_in(lst, envlst);
	else if (lst->redir->redir == 2)
		ft_redir_out(lst, envlst);
	else if (lst->redir->redir == 3)
		ft_redir_out_double(lst, envlst);
	else if (lst->redir->redir == 4)
		ft_redir_in_double(lst, envlst);
}
