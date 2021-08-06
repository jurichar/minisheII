#include "../includes/minishell.h"

int	check_built_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (is_built_in(lst) == TRUE)
	{
		g_exit_code = exec_built_in(lst, envlst, 1);
		return (1);
	}
	return (0);
}

int	exec_ve_abs(t_cmd_lst *lst, t_env_lst *envlst, pid_t pid)
{
	char	**args;

	args = join_args(lst->cmd, lst->args);
	if (pid < 0)
		perror("pid");
	else if (pid == 0)
	{
		if (execve(lst->cmd, args, lst->envp) == -1)
			g_exit_code = 1;
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
	return (g_exit_code);
}

int	exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst, pid_t pid)
{	
	char	**path;
	char	**args;
	char	*cmd;
	int		i;

	i = -1;
	path = ft_split(get_env_by_name(envlst, "PATH"), ':');
	if (!path)
		return (1);
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, lst->cmd);
		args = join_args(cmd, lst->args);
		if (execve(cmd, args, lst->envp) == -1)
			g_exit_code = errno;
	}
	free(args);
	free(path);
	return (g_exit_code);
}

int	exec_ve(t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;

	if (check_built_in(lst, envlst) == 1)
		return (1);
	pid = fork();
	if (pid < 0)
		perror("pid");
	else if (pid == 0)
	{
		exec_ve_abs(lst, envlst, pid);
		exec_ve_rel(lst, envlst, pid);
	}
	else
		waitpid(pid, NULL, 0);
	g_exit_code = errno;
	if (g_exit_code == 2)
		exit(g_exit_code);
	free(lst->cmd);
	free(lst->args);
	return (1);
}
