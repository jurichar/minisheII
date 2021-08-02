#include "../includes/minishell.h"

void	ft_redir(t_cmd_lst *lst)
{
	int	pid = fork();
	int status;
	int inout = lst->redir->redir;
	char *inoutput = lst->redir->arg;
	char BUF[128];

	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (inout == 1) // <
		{
			lst->fd[0] = open(inoutput, O_RDONLY);
			dup2(lst->fd[0], 0);
			close(lst->fd[0]);
		}
		else if (inout == 2) // >
		{
			lst->fd[1] = open(inoutput, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(lst->fd[1], 1);
			close(lst->fd[1]);
		}		
		else if (inout == 3) // >>
		{
			lst->fd[1] = open(inoutput, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(lst->fd[1], 1);
			close(lst->fd[1]);
		}
		// exec ?
		// else if (inout == 4) // <<
		// {
		// 	fd0 = open(inoutput, O_RDONLY);
		// 	dup2(fd0, 0);
		// 	read(fd0, BUF, ft_strlen(inoutput));
		// 	printf (">>> %s <<\n", BUF);
		// 	// while (ft_strcmp(BUF, inoutput) != 0)
		// 	// 	wait(NULL);
		// 	close(fd0);
		// }
	}
	else
	{
		waitpid(pid, &status, 0);
		exit(0);
	}
}
