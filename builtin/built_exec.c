/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:30:10 by jurichar          #+#    #+#             */
/*   Updated: 2021/09/13 03:35:14 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_built_in(t_cmd_lst *lst, t_env_lst **envlst, int fd)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		return (builtin_echo(lst, fd));
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		return (builtin_cd(lst, *envlst, 0));
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (builtin_exit());
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		return (builtin_unset(lst, envlst));
	else if (ft_strcmp(lst->cmd, "export") == 0)
		return (builtin_export(lst, envlst));
	else if (ft_strcmp(lst->cmd, "env") == 0)
		return (builtin_env(*envlst));
	return (0);
}

void	fd_close(int fd[2])
{
	dup2(fd[0], 0);
	if (fd[0] != 1)
		close(fd[0]);
	dup2(fd[1], 1);
	if (fd[1] != 1)
		close(fd[1]);
}

void	get_built_in(t_cmd_lst **lst, t_env_lst **envlst)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (!lst)
		return ;
	while (lst)
	{
		if ((*lst)->redir != NULL)
		{
			ft_redir(*lst, *envlst);
			exec_ve(*lst, envlst);
			unlink(".lol");
		}
		else if ((*lst)->sep == '|')
		{
			pipor(*lst, *envlst);
		}
		else
			exec_ve(*lst, envlst);
		break ;
	}
	fd_close(fd);
}
