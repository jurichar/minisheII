#include "../includes/minishell.h"

void spawn_proc (int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
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
        exec_ve (lst, envlst);
    }
    return ;
}

void fork_pipes (int n, t_cmd_lst *lst, t_env_lst *envlst)
{
    int i;
    int in, fd [2];
    in = 0;
    for (i = 0; i < n - 1 ; ++i)
    {
        pipe (fd);
        spawn_proc (in, fd [1], lst->next, envlst);
        close (fd [1]);
        in = fd [0];
    }
    if (in != 0)
        dup2 (in, 0);
    exec_ve (lst, envlst);
}

void pipor (t_cmd_lst *lst, t_env_lst *envlst)
{
    int i = 0;
    int n = lst->nb_p;
	fork_pipes (n + 1, lst, envlst);
}