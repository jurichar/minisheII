/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:34 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/07 17:45:53 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_built_in(t_cmd_lst *lst, t_env_lst **envlst)
{
	if (is_built_in(lst) == TRUE)
	{
		g_exit_code = exec_built_in(lst, envlst, 1);
		return (1);
	}
	return (0);
}

int	exec_ve_abs(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**args;

	args = join_args(lst->cmd, lst->args);
	ft_free_double_char(lst->envp);
	lst->envp = update_envp(envlst, get_env_size(envlst));
	if (execve(lst->cmd, args, lst->envp) == -1)
		g_exit_code = 1;
	ft_free_double_char(args);
	return (g_exit_code);
}

int	exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst)
{
	char	**path;
	char	**args;
	char	*cmd;
	char	*buf;
	int		i;

	i = -1;
	path = ft_split(get_env_by_name(envlst, "PATH"), ':');
	if (!path)
		return (1);
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], "/");
		buf = cmd;
		cmd = ft_strjoin(cmd, lst->cmd);
		args = join_args(cmd, lst->args);
		execve(cmd, args, lst->envp);
		ft_free_double_char(args);
		free(cmd);
		free(buf);
	}
	ft_free_double_char(path);
	return (g_exit_code);
}

void	exec_error(pid_t pid)
{
	int		status;
	int		signum ;

	signum = 0;
	if (waitpid(pid, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			signum = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			signum = WTERMSIG(status);
		else if (WIFSTOPPED(status))
			signum = WSTOPSIG(status);
		else
			printf("Something strange just happened.\n");
	}
	else
	{
		perror("waitpid() failed");
		exit(EXIT_FAILURE);
	}
	g_exit_code = signum;
}

int	exec_ve(t_cmd_lst *lst, t_env_lst **envlst)
{
	pid_t	pid;

	if (check_built_in(lst, envlst) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		perror("fork() failed (exec_ve)");
	else if (pid == 0)
	{
		exec_ve_abs(lst, *envlst);
		exec_ve_rel(lst, *envlst);
		printf("minishell: %s: command not found\n", lst->cmd);
		exit(EXIT_FAILURE);
	}
	else
		exec_error(pid);
	return (1);
}
