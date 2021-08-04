#include <unistd.h>

struct command
{
    const char **argv;
};

int spawn_proc (int in, int out, struct command *cmd)
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

int fork_pipes (int n, struct command *cmd)
{
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
        dup2 (in, 0);
    return execvp (cmd[i].argv[0], (char **)cmd[i].argv);
}

int main ()
{
  const char *ls[] = { "ls", "-l", 0 };
  const char *wc[] = { "wc", 0 };

  struct command cmd [] = { {ls}, {wc}} ;

  return fork_pipes (2, cmd);
}