/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/26 14:57:56 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_pipor	init_pipor(t_cmd_lst *lst)
{
	t_pipor	pip;
	int		i;

	pip.nbc = lst->nb_p + 1;
	pip.tpipes = (pip.nbc - 1) * 2;
	pip.pipes = malloc(sizeof(int) * pip.tpipes);
	pip.pid = malloc(sizeof(int) * pip.nbc);
	i = 0;
	while (i < pip.tpipes)
	{
		pipe(pip.pipes + i);
		i += 2;
	}
	return (pip);
}

void	fork_error(t_pipor pip, int i)
{
	if (pip.pid[i] < 0)
	{
		ft_putstr_fd("fork error\n", 2);
		exit(-1);
	}
}

void	clean_pid(t_pipor *pip)
{
	int	i;

	i = 0;
	while (i < pip->nbc)
	{
		waitpid(pip->pid[i], NULL, 0);
		i++;
	}
}

int	pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	t_pipor	pip;
	int		i;

	pip = init_pipor(lst);
	i = -1;
	while (++i < pip.nbc)
	{
		pip.pid[i] = fork();
		fork_error(pip, i);
		if (pip.pid[i] == 0)
		{
			if (i == 0)
				pipor_first(pip, lst, envlst);
			else if (i == pip.nbc - 1)
				pipor_mid(pip, lst, envlst);
			else
				pipor_last(pip, lst, envlst, i);
		}
		lst = lst->next;
	}
	close_pipor(&pip);
	clean_pid(&pip);
	free (pip.pipes);
	free (pip.pid);
	return (0);
}
