/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 05:49:00 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/27 23:16:08 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_pipor(t_pipor *pip)
{
	int	i;

	i = 0;
	while (i < pip->tpipes)
	{
		close(pip->pipes[i]);
		i++;
	}
}

void	pipor_first(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst)
{
	dup2(pip.pipes[1], 1);
	close_pipor(&pip);
	if (lst->redir != NULL)
		ft_redir(lst, envlst);
	exec_ve(lst, &envlst);
	exit(1);
}

void	pipor_mid(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst)
{
	dup2(pip.pipes[pip.tpipes - 2], 0);
	close_pipor(&pip);
	if (lst->redir != NULL)
		ft_redir(lst, envlst);
	exec_ve(lst, &envlst);
	exit(1);
}

void	pipor_last(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst, int i)
{
	dup2(pip.pipes[i + (i - 2)], 0);
	dup2(pip.pipes[i + i + 1], 1);
	close_pipor(&pip);
	if (lst->redir != NULL)
		ft_redir(lst, envlst);
	exec_ve(lst, &envlst);
	exit(1);
}
