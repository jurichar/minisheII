#include "../includes/minishell.h"

int exec_ve(t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid = -1;
	char	**args = NULL;
	char 	**path = NULL;
	char 	*cmd = NULL;
	int err;
	int i = 0;
	err = 0;

	if (is_built_in(lst) == TRUE)
    {
        printf("builtin\n");
		exec_built_in(lst, envlst, 1);
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
			err = 1;
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
                printf ("coucou\n");
                err = 1;
            }
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
        i++;
	}
	if (err == 1)
	{
		exit(0);
	}
    free(lst->cmd);
	free(lst->args);
	free(args);
	return 1;
}