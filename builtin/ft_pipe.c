/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/19 18:43:32 by jurichar         ###   ########.fr       */
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
	int i = 0;
	int pipefds[2];
	pid_t pid[2];
	int numPipes = lst->nb_p;

	


}

int pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int numPipes = lst->nb_p;
	int status;
	int i = 0;
	pid_t pid[numPipes - 1];
	int pipefds[2*numPipes];
	printf ("nb of p = %d\n", numPipes);
	for(i = 0; i < (numPipes * 2); i++)
	{
		if(pipe(pipefds + (i * 2)) < 0) {
			perror("couldn't pipe");
			exit(EXIT_FAILURE);
		}
	}
	int x = 0;
	int j = 0;
	while(x <= (numPipes)) 
	{
		pid[x] = fork();
		if(pid[x] < 0)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		else if(pid[x] == 0) 
		{
			if(x == 0)
			{
				//dup2(pipefds[0], 0); // dup2(fd[0], 0) okk 1000%
				dup2(pipefds[1], 1); // dup2(fd[1], 1)okkkk00%
				for(i = 0; i < numPipes * 2; i++) // close all fds
					close(pipefds[i]);
			printf(" ici ?%d",exec_ve(lst, &envlst));
			
			}
			else //if(j == numPipes * 2)
			{
				dup2(pipefds[0], 0); // dup2(fd[0], 0)
				for(i = 0; i < numPipes * 2; i++) // close all fds
					close(pipefds[i]);
			printf(" ici ?%d",exec_ve(lst, &envlst));
			}
		//	write(2, "ici\n", 4);
		//	ft_putstr_fd(ft_itoa(j), 2);
			// else if(j != 0 )
			// {
			// 	dup2(pipefds[j - 2], 0);
			// 	dup2(pipefds[j - 1], 1);
			// }
		}
		lst = lst->next;
		j+=2;
		x++;
	}

	for(i = 0; i < (numPipes * 2); i++){
		close(pipefds[i]);
	}
	for(i = 0; i < (numPipes - 1) ; i++)
		waitpid(pid[i], NULL,0);

	for(i = 0; i < (numPipes + 1) ; i++)
		wait(&status);
	return 0;
}
*/