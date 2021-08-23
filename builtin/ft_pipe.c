/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:29:55 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/23 14:41:08 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
	int nbc;
	nbc = lst->nb_p + 1;
	int pid[nbc];
	int tpipes;
	tpipes = (nbc - 1) * 2;
	int pipes[tpipes];
	int x;

	x = 0;
	while(x < tpipes)
	{ 
		pipe(pipes + x);
		x += 2;
	}
	int i = 0;
	while (i < nbc)
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
				for(int x = 0; x < tpipes; x++)
					close(pipes[x]);
				exec_ve(lst, &envlst);
				exit(1);
			}
			else if(i == nbc - 1) // last
			{
				dup2(pipes[tpipes - 2], 0);
				for(int x = 0; x < tpipes; x++)
					close(pipes[x]);
				if (lst->redir != NULL)
					ft_redir(lst, envlst);
				exec_ve(lst, &envlst);
				exit(1);
			}
			else // other cmd
			{
				dup2(pipes[i + (i - 2)], 0);
				dup2(pipes[i + i + 1], 1);
				for(int x = 0; x < tpipes; x++)
					close(pipes[x]);
				exec_ve(lst, &envlst);
				exit(1);
			}
		}
		i++;
		lst = lst->next;
	}
	x = 0;
	while(x < tpipes)
	{
		close(pipes[x]);
		x++;
	}
	
	x = 0;
	while (x < nbc)
	{
		waitpid(pid[x], NULL, 0);
		x++;
	}
	return 0;
}