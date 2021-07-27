#include <libc.h>

int main (int ac, char **av, char **envp)
{
    char *cmd[2];
    char cmd[0] = "/bin/ls";
    char cmd[1] = "/usr/bin/wc";
    char *arg1[] = {"/bin/ls","NULL"};
    char *arg1[] = {"/usr/bin/wc","NULL"};
    int fd[2];

	pipe(fd);
	int	pid;
	int	pid2;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
        execvp("ls",{"ls","NULL"})
		pid2 = fork();
		if (pid2 < 0)
			perror("fork");
		else if (pid2 == 0)
		{
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
	}
	close (fd[0]);
	close (fd[1]);
	waitpid(pid2, 0, 0);
	waitpid(pid, 0, 0);
}