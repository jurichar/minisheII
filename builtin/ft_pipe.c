/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/20 13:12:27 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;
	(void ) lst;
	(void ) envst;

	pid = fork();
	if (pid < 0)
		perror("pid");
	if ((pid) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			 close(out);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			 close(in);
			close(out);
		}
		// exec_ve(lst, &envlst);
		// exit(0);
	}
	else
	{
		close (in);
		close(out);
		waitpid(pid, NULL, 0);
	}
	return (pid);
}

int	pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int		n;
	int		i;
	int		in;
	int		fd[2];

	n = lst->nb_p;
	i = -1;
	in = 0;
	while (++i < n)
	{
		pipe(fd);
		forkito (in, fd[1], lst, envlst);
		close (fd[1]);
		in = fd[0];
		lst = lst->next;
	}
	if (in != 0)
	{
		dup2 (in, 0);
	}
	return (exec_ve(lst, &envlst));
	// if ((lst)->redir != NULL)
	// {
	// 	ft_redir(lst, envlst);
	// 	return (exec_ve(lst, &envlst));
	// }
	// else
}

/*
int pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int commandNr = lst->nb_p;
	int pid[commandNr];

	int totalPipes = (commandNr - 1) * 2;
	int pipes[totalPipes];

	// Initializing pipes
	for(int x = 0; x < totalPipes; x += 2)
		pipe(pipes + x);

	for (int i = 0; i < commandNr; i++)
	{
		if ((pid[i] = fork()) < 0) 
		{
		printf("*** ERROR: forking child process failed\n");
		exit(-1);
		}
		else if (pid[i] == 0)
		{
			if(i == 0)
			{
				dup2(pipes[1], 1);
				for(int x = 0; x < totalPipes; x++)
					close(pipes[x]);
				exec_ve(lst, envlst);
				perror("Wrong Command Specified!");
				exit(1);
			}
			else if(i == commandNr - 1)
			{
				dup2(pipes[totalPipes - 2], 0);
				for(int x = 0; x < totalPipes; x++)
				close(pipes[x]);
				exec_ve(lst, envlst);
				perror("Wrong Command Specified!");
				exit(1);
			}
			else
			{
				dup2(pipes[i + (i - 2)], 0);
				dup2(pipes[i + i + 1], 1);
				for(int x = 0; x < totalPipes; x++)
					close(pipes[x]);
				exec_ve(lst, envlst);
				perror("Wrong Command Specified!");
				exit(1);
			}
			lst = lst->next;
		}
	}
	// close pipes
	for(int x = 0; x < totalPipes; x++)
		close(pipes[x]);

	for (int i = 0; i < commandNr; i++)
		waitpid(pid[i], NULL, 0);
	return 0;
}
*/