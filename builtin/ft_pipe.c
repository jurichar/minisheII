/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/12 13:58:25 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid = 0;

	pid = fork();
	if (pid < 0)
		perror("pid");
	if ((pid) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		exec_ve(lst, envlst);
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (pid);
}

int	pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int		n;
	int		i;
	int		in;

	n = lst->nb_p;
	i = -1;
	in = 0;
	while (++i < n)
	{
		pipe(lst->fd);
		forkito (in, lst->fd[1], lst, envlst);
		close (lst->fd[1]);
		in = lst->fd [0];
		lst = lst->next;
	}
	if (in != 0)
	{
		dup2 (in, 0);
	}
	if ((lst)->redir != NULL)
	{
		ft_redir(lst, envlst);
		return exec_ve(lst, envlst);
	}
	else
		return (exec_ve(lst, envlst));
}
