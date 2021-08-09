#include "../includes/minishell.h"

int	exec_built_in(t_cmd_lst *lst, t_env_lst *envlst, int fd)
{
	if (ft_strcmp(lst->cmd, "echo") == 0)
		return (builtin_echo(lst, envlst, fd));
	else if (ft_strcmp(lst->cmd, "cd") == 0)
		return (builtin_cd(lst, envlst, 0));
	else if (ft_strcmp(lst->cmd, "exit") == 0)
		return (builtin_exit(lst));
	else if (ft_strcmp(lst->cmd, "pwd") == 0)
		return (builtin_pwd(lst, envlst));
	else if (ft_strcmp(lst->cmd, "env") == 0)
		return (builtin_env(lst, envlst));
	else if (ft_strcmp(lst->cmd, "unset") == 0)
		return (builtin_unset(lst, envlst));
	else if (ft_strcmp(lst->cmd, "export") == 0)
		return (builtin_export(lst, envlst));
	return (0);
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

char	*get_env_by_name(t_env_lst *envlst, char *name)
{
	if (!envlst)
		return (0);
	while (envlst)
	{
		if (ft_strcmp(envlst->name, name) == 0)
			return (envlst->content);
		envlst = envlst->next;
	}
	return (0);
}

int	is_built_in(t_cmd_lst *lst)
{
	char	**builtin_list;
	int		builtin;
	int		i;
	
	builtin_list = malloc(sizeof(char *) * 2);
	if (!builtin_list)
		return (0);
	builtin_list[0] = ft_strdup("cd");
	builtin_list[1] = ft_strdup("export");
	builtin_list[2] = ft_strdup("export");
	builtin_list[3] = ft_strdup("export");
	builtin_list[4] = ft_strdup("export");
	builtin_list[5] = ft_strdup("export");
	builtin_list[6] = ft_strdup("exit");
	builtin_list[7] = NULL;
	builtin = FALSE;
	i = -1;
	while (builtin_list[++i] && i <= 8)
	{
		if (ft_strcmp(builtin_list[i], lst->cmd) == 0)
		{
			builtin = TRUE;
			break ;
		}
	}
	return (builtin);
}

void	fd_close(int fd[2])
{
	dup2(fd[0], 0);
	close(fd[0]);
	dup2(fd[1], 1);
	close(fd[1]);
}

void	get_built_in(t_cmd_lst **lst, t_env_lst *envlst, char **envp)
{
	int i;
	int builtin;
	int fd[2];
	pid_t	pid;

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (!lst)
		return;
	while (lst)
	{
		if ((*lst)->redir != NULL)
		{
			ft_redir(*lst, envlst);
			exec_ve(*lst, envlst);
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			return ;
		}
		else if ((*lst)->sep == '|')
		{
			pipor(*lst, envlst);
			// exec_ve(*lst, envlst);
			dup2(fd[0], 0);
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			return ;
		}
		else
			exec_ve(*lst, envlst);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if ((*lst)->next && (*lst)->sep == ';')
		{
			*lst = (*lst)->next;
			get_built_in(lst, envlst, envp);
		}
		break;
	}
	if (fd[0] != 1)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}
