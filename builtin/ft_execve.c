#include "../includes/minishell.h"

int	exec_ve(t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;
	char	**args = NULL;
	char 	**path = NULL;
	char 	*cmd = NULL;
	int i = 0;

	if (is_built_in(lst) == TRUE)
	{
		g_exit_code = exec_built_in(lst, envlst, 1);
		return 1;
	}
	pid = fork();
	path = ft_split(get_env_by_name(envlst, "PATH"), ':'); //path =  bin/ usr/bin ...
	if (!path)
		return (1);
	args = join_args(lst->cmd, lst->args); // join ls + args
	if (pid == 0)
	{
		if (execve(lst->cmd, args, lst->envp) == -1)
		{
			g_exit_code = 1;
		}
	}
	while (path[i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, lst->cmd);
		args = join_args(cmd, lst->args);
		if (pid < 0)
			perror("pid");
		else if (pid == 0)
		{
			if (execve(cmd, args, lst->envp) == -1)
			{
				g_exit_code = errno;
				printf("COUCOU errno == %d\n", errno);
			}
		}
		else
			waitpid(pid, NULL, 0);
		i++;
	}
	printf("errno == %d\n", errno);
	if (errno == 10)
		g_exit_code = 0;
	if (errno == 2)
	{
		g_exit_code = 127;
		exit(127);
	}
	free(lst->cmd);
	free(lst->args);
	free(args);
	free(path);
	return 1;
}
