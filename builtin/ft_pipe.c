#include "../includes/minishell.h"
struct command
{
    const char **argv;
};
int spawn_proc(int in, int out, struct command *cmd)
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

int pipor (t_cmd_lst *lst, t_env_lst *envlst)
{
    int n = 3;
    int i;
    pid_t pid;
    int in, fd [2];
    const char *ls[] = { "ls", "-l", 0 };
    const char *wc[] = { "wc", 0 };
    const char *cat[] = { "cat", "-e", 0 };
    t_cmd cmd[3];
    //struct command *cmd;
    // cmd = malloc(n * sizeof(struct command));
    // struct command cmd [] = { {ls}, {wc}, {cat}} ;
    cmd[0].argv = ls;
    cmd[1].argv = wc;
    cmd[2].argv = cat;

    // while (lst)
    // {
    //     cmds[i].argv = join_args(lst->cmd, lst->args);
    //     i++;
    //     lst = lst->next;
    // }

    in = 0;
    for (i = 0; i < n - 1; ++i)
    {
        pipe (fd);
        spawn_proc (in, fd [1], cmd + i);
        close (fd [1]);
        in = fd [0];
    }
    if (in != 0)
    {
        dup2 (in, 0);
    }
    return execvp (cmd[i].argv[0], (char **)cmd[i].argv);
}