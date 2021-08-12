#include <unistd.h>
#include <stdio.h>

struct command
{
    const char **argv;
};

int spawn_proc (int in, int out, struct command *cmd)
{
    // all cmd execpt last
    printf ("cmd = %s\n", cmd->argv[0]);
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

int main ()
{
    const char *ls[] = { "cat", 0 };
    const char *wc[] = { "cat", 0 };
    const char *cat[] = { "ls", 0 };

    struct command cmd [] = { {ls}, {wc}, {cat}} ;

    int n = 3;
    int i;
    pid_t pid;
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
    {
        dup2 (in, 0);
    }
    return execvp (cmd[i].argv[0], (char **)cmd[i].argv);
}