#include "../includes/minishell.h"

int spawn_proc (int in, int out, t_cmd *cmd, t_cmd_lst *lst)
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

int fork_pipes (int n, t_cmd *cmd, t_cmd_lst *lst)
{
    int i;
    int in, fd [2];
    in = 0;
    for (i = 0; i < n - 1 ; ++i)
    {
        pipe (fd);
        spawn_proc (in, fd [1], cmd + i, lst);
        close (fd [1]);
        in = fd [0];
    }
    if (in != 0)
    dup2 (in, 0);
    return execvp (cmd[i].argv[0], (char **)cmd[i].argv);
}

int pipor (t_cmd_lst *lst)
{
    int i = 0;
    int n = lst->nb_p;
	t_cmd *args;
    while (i < n + 1)
    {
	    args[i].argv = join_args(lst->cmd, lst->args);
	    lst = lst->next;
        i++;
    }
	return fork_pipes (n + 1, args, lst);
}