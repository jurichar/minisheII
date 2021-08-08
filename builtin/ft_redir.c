/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/08 19:25:12 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_redir_in_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	BUF[128];

	lst->fd[0] = open(lst->redir->arg, O_RDONLY);
	dup2(lst->fd[0], 0);
	read(lst->fd[0], BUF, ft_strlen(lst->redir->arg));
	while (ft_strcmp(BUF, lst->redir->arg) != 0)
		wait(NULL);
	close(lst->fd[0]);
}

void	ft_redir_out_double(t_cmd_lst *lst, t_env_lst *envlst)
{
	lst->fd[1] = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0644);
	dup2(lst->fd[1], 1);
	close(lst->fd[1]);
}

void	ft_redir_out(t_cmd_lst *lst, t_env_lst *envlst)
{
	lst->fd[1] = open(lst->redir->arg, O_CREAT | O_RDWR | O_TRUNC, 0644);
	dup2(lst->fd[1], 1);
	close(lst->fd[1]);
}

void	ft_redir_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	lst->fd[0] = open(lst->redir->arg, O_RDONLY);
	dup2(lst->fd[0], 0);
	close(lst->fd[0]);
}

void	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
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
	else
	{
		waitpid(pid, NULL, 0);
		exit(0);
	}
}
