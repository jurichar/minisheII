#include "../includes/minishell.h"

int forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst)
{
    pid_t pid;
    if ((pid = fork()) == 0)
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
    return pid;
}

int pipor (t_cmd_lst *lst, t_env_lst *envlst)
{
    int n = lst->nb_p;
    int i;
    pid_t pid;
    int in, fd [2];
    i = 0;
    in = 0;

    for (i = 0; i < n; ++i)
    {
        pipe(fd);
        forkito (in, fd[1], lst, envlst);
        close (fd[1]);
        in = fd [0];
        lst = lst->next;
    }
    if (in != 0)
    {
        dup2 (in, 0);
    }
    return exec_ve (lst, envlst);
}