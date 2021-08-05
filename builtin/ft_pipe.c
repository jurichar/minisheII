#include "../includes/minishell.h"

int forkito(int in, int out, t_cmd *cmd, t_cmd_lst *lst, t_env_lst *envlst)
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
        return execvp (cmd->argv[0], cmd->argv);
    }
    return pid;
}

int pipor (t_cmd_lst *lst, t_env_lst *envlst)
{
    int n = lst->nb_p + 1;
    int i;
    pid_t pid;
    int in, fd [2];
	char	**args = NULL;
    t_cmd cmd[n];
    i = 0;
    while (i < n - 1)
    {
        cmd[i].argv = join_args(lst->cmd, lst->args);
        i++;
        lst = lst->next;
    }
    in = 0;
    for (i = 0; i < n - 1; ++i)
    {
        pipe(fd);
        forkito (in, fd[1], cmd + i, lst, envlst);
        close (fd[1]);
        in = fd [0];
        // lst = lst->next;
    }
    if (in != 0)
    {
        dup2 (in, 0);
    }
    return exec_ve (lst, envlst);
}