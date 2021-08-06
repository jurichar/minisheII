#include "../includes/minishell.h"

void	ft_osef(void *pouet)
{
	pouet = (void *)42;
}

int	forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;

	pid = fork();
	if (pid < 1)
		perror("pid");
	else if ((pid) == 0)
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
		exec_ve (lst, envlst);
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
	pid_t	pid;
	int		in;

	n = lst->nb_p;
	i = -1;
	in = 0;
	while (i < n)
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
	return (exec_ve(lst, envlst));
}
