/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/20 16:23:42 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int commandNr;
	commandNr = lst->nb_p + 1;
	int pid[commandNr];
	int totalPipes;
	totalPipes = (commandNr - 1) * 2;
	int pipes[totalPipes];
	int x;

	x = 0;
	while(x < totalPipes)
	{ 
		pipe(pipes + x);
		x += 2;
	}

	int i = 0;
	while (i < commandNr)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
		printf("fork error\n");
		exit(-1);
		}
		else if (pid[i] == 0)
		{
			if(i == 0) // first cmd
			{
				dup2(pipes[1], 1);
				for(int x = 0; x < totalPipes; x++)
					close(pipes[x]);
				exec_ve(lst, &envlst);
				exit(1);
			}
			else if(i == commandNr - 1) // last
			{
				dup2(pipes[totalPipes - 2], 0);
				for(int x = 0; x < totalPipes; x++)
					close(pipes[x]);
				// if (lst->redir != NULL)
				// 	ft_redir(lst, envlst);
				exec_ve(lst, &envlst);
				exit(1);
			}
			else // other cmd
			{
				dup2(pipes[i + (i - 2)], 0);
				dup2(pipes[i + i + 1], 1);
				for(int x = 0; x < totalPipes; x++)
					close(pipes[x]);
				exec_ve(lst, &envlst);
				exit(1);
			}
		}
		i++;
		lst = lst->next;
	}
	x = 0;
	while(x < totalPipes)
	{
		close(pipes[x]);
		x++;
	}
	
	x = 0;
	while (x < commandNr)
	{
		waitpid(pid[i], NULL, 0);
		x++;
	}
	return 0;
}