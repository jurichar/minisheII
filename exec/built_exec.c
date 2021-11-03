/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:30:10 by jurichar          #+#    #+#             */
/*   Updated: 2021/11/03 10:24:46 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_built_in(t_cmd_lst *lst, t_env_lst **envlst, int fd)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		return (builtin_echo(lst, fd));
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		return (builtin_cd(lst, envlst, 0));
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (builtin_exit(lst, *envlst));
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

void	find_next_cmd(char sep, t_cmd_lst **lst)
{
	int	sep_phlvl;

	sep_phlvl = (*lst)->sep_phlvl;
	if (sep == AND)
	{
		while ((*lst) && !((*lst)->sep_phlvl <= sep_phlvl && (*lst)->sep == OR))
			*lst = (*lst)->next;
	}
	else
	{
		while ((*lst) && !((*lst)->sep_phlvl <= sep_phlvl
				&& (*lst)->sep == AND))
			*lst = (*lst)->next;
	}
}

void	and_or_manager(t_cmd_lst **lst, t_env_lst **envlst)
{
	if ((*lst)->sep == AND && g_exit_code == 0)
		get_built_in(&(*lst)->next, envlst, 0);
	else if ((*lst)->sep == OR && g_exit_code != 0)
		get_built_in(&(*lst)->next, envlst, 0);
	else if (((*lst)->sep == AND && g_exit_code != 0)
		|| ((*lst)->sep == OR && g_exit_code == 0))
	{
		find_next_cmd((*lst)->sep, lst);
		if (*lst)
			get_built_in(&(*lst)->next, envlst, 0);
	}
}

void	get_built_in(t_cmd_lst **lst, t_env_lst **envlst, int i)
{
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	(*lst)->cmd = find_env_var((*lst)->cmd, *envlst, -1, 0);
	expand_before_exec(lst, *envlst, 0);
	if ((*lst)->sep == '|')
		pipor(*lst, *envlst);
	else if ((*lst)->redir != NULL)
	{
		i = ft_redir(*lst, *envlst, 0);
		if (i == 1)
			exec_ve(*lst, envlst);
	}
	else
		exec_ve(*lst, envlst);
	and_or_manager(lst, envlst);
	fd_close(fd);
}
