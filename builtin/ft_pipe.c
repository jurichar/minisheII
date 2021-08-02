#include "../includes/minishell.h"

int spawn_proc (int in, int out, t_cmd *cmd)
{
    pid_t pid;
    if ((pid = fork()) == 0)
    {
        if (in != 0)
        {
            dup2 (in, 0);
            close (in);
        }
        if (out != 1)
        {
            dup2 (out, 1);
            close (out);
        }
        return execvp (cmd->argv [0], (char * const *)cmd->argv);
    }
    return pid;
}

int fork_pipes (int n, t_cmd *cmd)
{
    int i;
    int in, fd [2];

    in = 0;
    for (i = 0; i < n - 1; ++i)
    {
        pipe (fd);
        spawn_proc (in, fd [1], cmd + i);
        close (fd [1]);
        in = fd [0];
    }
    if (in != 0)
    dup2 (in, 0);
    return execvp (cmd[i].argv[0], (char **)cmd[i].argv);
}

int pipor (t_cmd_lst *lst)
{
	char **args;
	char **args2;
	char **args3;
	args = join_args(lst->cmd, lst->args);
	lst = lst->next;
  	args2 = join_args(lst->cmd, lst->args);
	// ls | wc | cat -e
	// lst = lst->next;
  	// args3 = join_args(lst->cmd, lst->args);
	t_cmd cmd[] = {{args}, {args2} } ;
	return fork_pipes (2, cmd);
}