#include "../includes/minishell.h"

int spawn_proc(int in, int out, t_cmd *cmd)
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
        return execvp(cmd->argv[0], (char *const *)cmd->argv);
    }
    return pid;
}

int fork_pipes(int n, t_cmd *cmd)
{
    int i;
    int in, fd[2];

    in = 0;
}

void pipor(t_cmd_lst *lst, t_env_lst *envlst)
{
    int in = 0;
    int i = 0;
    int n = lst->nb_p;
    t_cmd *cmds = NULL;
    cmds = malloc(n * sizeof(t_cmd));
    while (lst)
    {
        cmds[i].argv = join_args(lst->cmd, lst->args);
        i++;
        lst = lst->next;
    }
    n = n + 1;
    int j;
    // fork_pipes(n + 1, cmds);
    for (j = 0; j < n - 1; ++j)
    {
        pipe(lst->fd);
        spawn_proc(in, lst->fd[1], cmds + j);
        close(lst->fd[1]);
        in = lst->fd[0];
    }
    if (in != 0)
        dup2(in, 0);
    execvp(cmds[j].argv[0], (char **)cmds[j].argv);
}