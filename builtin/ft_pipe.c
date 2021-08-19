/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/19 16:26:21 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/*
int	forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;

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
		exit(g_exit_code);
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
		return (exec_ve(lst, envlst));
	}
	else
		return (exec_ve(lst, envlst));
}


int pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int n = lst->nb_p;
	int pipefds[2];

	for( i = 0; i < n; i++ )
	{
		if(pipe(pipefds + i*2) < 0)
		{
			perror(lol);
		}
	}

	commandc = 0
	while(lst->next)
	{
		pid = fork()
		if( pid == 0 )
		{
			if( not first command ){
				if( dup2(pipefds[(commandc-1)*2], 0) < ){
					perror and exit
				}
			}
			/* child outputs to next command, if it's not
				the last command */
			if( not last command ){
				if( dup2(pipefds[commandc*2+1], 1) < 0 ){
					perror and exit
				}
			}
			close all pipe-fds
			execvp
			perror and exit
		} else if( pid < 0 ){
			perror and exit
		}
		cmd = cmd->next
		commandc++
	}

	for( i = 0; i < 2 * n; i++ )
	{
		close(pipefds[i]);
	}
}
*/
