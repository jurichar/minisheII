#include "../includes/minishell.h"

char	*builtin_list[] = {
	"cd",
	"echo",
	"pwd",
	"exit",
	"export",
	"env",
	"unset"
};

// print_lst(t_cmd_lst *lst)
// {
// 	while (lst)
// 	{
// 		"cmprintf(d = %s\n", lst->cmd);
// 		lst = lst->next;
// 	}
// }

int exec_built_in(t_cmd_lst *lst, t_env_lst *envlst, int fd)
{
	if (ft_strcmp(lst->cmd,"echo") == 0)
		return builtin_echo(lst, envlst, fd);
	else if (ft_strcmp(lst->cmd,"cd") == 0)
		return builtin_cd(lst, envlst);
	else if (ft_strcmp(lst->cmd,"exit") == 0)
		return builtin_exit(lst);
	else if (ft_strcmp(lst->cmd,"pwd") == 0)
		return builtin_pwd(lst, envlst);
	else if (ft_strcmp(lst->cmd,"env") == 0)
		return builtin_env(lst, envlst);
	else if (ft_strcmp(lst->cmd,"unset") == 0)
		return builtin_unset(lst, envlst);
	//else if (ft_strcmp(lst->cmds[0],"export") == 0)
	//	return builtin_export(lst, envlst);
	close (fd);
	return 0;
}

char	**join_args(char *s, char **args)
{
	char	**new;
	int		len;
	int		i;

	len = 0;
	while (args[len])
		len++;
	new = malloc(sizeof(char *) * (len + 2));
	len = 0;
	i = 1;
	new[0] = s;
	while (args[len])
	{
		new[i] = args[len];
		i++;
		len++;
	}
	new[i] = NULL;
	return (new);
}

// fork_child(int in, int out, int fd_to_close)
// {
	
// }

void	pipex(t_cmd_lst **lst)
{
	int i = -1;
	int fds[2];
	pipe((*lst)->fd);
	pid_t	pid;
	pid_t	pid2;

	pid = fork();
	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		dup2((*lst)->fd[1], STDOUT_FILENO);
		close((*lst)->fd[1]);
		close((*lst)->fd[0]);
		pid2 = fork();
		if (pid2 < 0)
			perror("fork");
		else if (pid2 == 0)
		{
			dup2((*lst)->fd[0], STDIN_FILENO);
			close((*lst)->fd[0]);
			close((*lst)->fd[1]);
		}
	}
	close ((*lst)->fd[0]);
	close ((*lst)->fd[1]);
	waitpid(pid2, 0, 0);
	waitpid(pid, 0, 0);
}

void	redir(t_cmd_lst *lst)
{
	int	pid = fork();
	int fd0;
	int fd1;
	int status;
	int inout = lst->redir->redir;
	char *inoutput = lst->redir->arg;
	char BUF[128];

	if (pid < 0)
		perror("fork");
	else if (pid == 0)
	{
		if (inout == 1) // <
		{
			fd0 = open(inoutput, O_RDONLY);
			dup2(fd0, 0);
			close(fd0);
		}
		else if (inout == 2) // >
		{
			fd1 = open(inoutput, O_CREAT | O_RDWR | O_TRUNC, 0644);
			dup2(fd1, 1);
			close(fd1);
		}		
		else if (inout == 3) // >>
		{
			fd1 = open(inoutput, O_CREAT | O_RDWR | O_APPEND, 0644);
			dup2(fd1, 1);
			close(fd1);
		}
		// exec ?
		// else if (inout == 4) // <<
		// {
		// 	fd0 = open(inoutput, O_RDONLY);
		// 	dup2(fd0, 0);
		// 	read(fd0, BUF, ft_strlen(inoutput));
		// 	printf (">>> %s <<\n", BUF);
		// 	// while (ft_strcmp(BUF, inoutput) != 0)
		// 	// 	wait(NULL);
		// 	close(fd0);
		// }
	}
	else
	{
		waitpid(pid, &status, 0);
		exit(0);
	}
}

char **get_envchar(t_cmd_lst *lst, t_env_lst *envlst)
{
	char **str;
	int i = 0;
	str = malloc (1000);
	while (envlst)
	{
		str[i] = ft_strjoin(envlst->name, "=");
		str[i] = ft_strjoin(str[i], envlst->content);
		i++;
		envlst = envlst->next;
	}
	// print_point_char(str);
	return str;
}

char *get_env_by_name(t_env_lst *envlst, char *name)
{
	if (!envlst)
		return 0;
	while (envlst)
	{
		if (ft_strcmp(envlst->name, name) == 0)
			return (envlst->content);
		envlst = envlst->next;
	}
	return 0;
}

int exec_ve(t_cmd_lst *lst, int builtin, t_env_lst *envlst, char **envp)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	char	**args;
	char	**str;
	pid = fork();
	char **path;
	int i = 0;
	int err;

	err = 0;

	path = ft_split(get_env_by_name(envlst, "PATH"), ':'); //path =  bin/ usr/bin ...
	if (!path)
		return (1);
	args = join_args(lst->cmd, lst->args); // join ls + args
	//print_point_char(args);
	if (pid == 0)
	{
		if (execve(lst->cmd, args, envp) == -1)
		{
			err = 1;
		}
	}
	while (path[i])
	{
	char *cmd = ft_strjoin(path[i], "/");
	cmd = ft_strjoin(cmd, lst->cmd);
	args = join_args(cmd, lst->args);
	if (pid < 0)
		perror("BDSM");
	else if (pid == 0)
	{
		if (execve(cmd, args, envp) == -1)
		{
			err = 1;
		}
		else 
		{
			perror("pid");
		}
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	i++;
	}
	if (err == 1)
	{
		exit(0);
	}
	free(lst->args);
	free(args);
	return 1;
}

void get_built_in(t_cmd_lst **lst, t_env_lst *envlst, char **envp)
{
	int	i;
	int	j;
	int	builtin;
	(*lst)->fd[0] = dup(0);
	(*lst)->fd[1] = dup(1);
	pid_t	pid;
	if (!lst)
		return ;
	if ((*lst)->redir != NULL)
		redir(*lst);
	if ((*lst)->sep == '|')
	{
		pipex(lst);
	}
	while (lst)
	{
		builtin = 0;
		i = -1;
		while (builtin_list[++i])
			if (ft_strcmp(builtin_list[i], (*lst)->cmd) == 0)
			{
				builtin = TRUE;
				break ;
			}
		if (builtin == TRUE)
		{
			exec_built_in(*lst, envlst, 1);
		}
		else
		{
			exec_ve(*lst, builtin, envlst, envp);
		}
		dup2((*lst)->fd[0], 0);
		close((*lst)->fd[0]);
		dup2((*lst)->fd[1], 1);
		close((*lst)->fd[1]);
		if ((*lst)->next && (*lst)->sep == ';') 
		{ // faut pas le gerer mais bon on le gere :/
			*lst = (*lst)->next;
			get_built_in(lst, envlst, envp);
		}
		break ;
	}
	if ((*lst)->fd[0] != 1)
		close((*lst)->fd[0]);
	if ((*lst)->fd[1] != 1)
		close((*lst)->fd[1]);
}
