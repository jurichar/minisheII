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

int	is_built_in(t_cmd_lst *lst)
{
	int builtin;
	int i;
	builtin = 0;
	i = -1;
	while (builtin_list[++i])
	{
		if (ft_strcmp(builtin_list[i], lst->cmd) == 0)
		{
			builtin = TRUE;
			break ;
		}
	}
	return builtin;
}

void get_built_in(t_cmd_lst **lst, t_env_lst *envlst, char **envp)
{
	int	i;
	int	builtin;
	int fd[2];
// (*lst)->
	fd[0] = dup(0);
	fd[1] = dup(1);
	if (!lst)
		return ;

	while (lst)
	{
		// pid_t pid;
		// if ((pid = fork()) == 0)
		// {
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
		if ((*lst)->sep == '|')
		{
				pipor(*lst, envlst);
		}
		exec_ve(*lst, envlst);
		dup2(fd[0], 0);
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		if ((*lst)->next && (*lst)->sep == ';')
		{ // faut pas le gerer mais bon on le gere :/
			*lst = (*lst)->next;
			get_built_in(lst, envlst, envp);
		}
		break ;
	}
	if (fd[0] != 1)
		close(fd[0]);
	if (fd[1] != 1)
		close(fd[1]);
}
