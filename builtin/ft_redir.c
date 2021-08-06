#include "../includes/minishell.h"

void	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	int		status;
	int		inout;
	pid_t	pid;
	char	*inoutput;
	char	BUF[128];

	pid = fork();
	inoutput = lst->redir->arg;
	inout = lst->redir->redir;
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (inout == 1)
		{
			lst->fd[0] = open(inoutput, O_RDONLY);
			dup2(lst->fd[0], 0);
			close(lst->fd[0]);
		}
		else if (inout == 2)
		{
			lst->fd[1] = open(inoutput, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(lst->fd[1], 1);
			close(lst->fd[1]);
		}		
		else if (inout == 3)
		{
			lst->fd[1] = open(inoutput, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(lst->fd[1], 1);
			close(lst->fd[1]);
		}
		else if (inout == 4)
		{
			lst->fd[0] = open(inoutput, O_RDONLY);
			dup2(lst->fd[0], 0);
			read(lst->fd[0], BUF, ft_strlen(inoutput));
			while (ft_strcmp(BUF, inoutput) != 0)
				wait(NULL);
			close(lst->fd[0]);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		exit(0);
	}
}
