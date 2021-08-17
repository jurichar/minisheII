/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:34 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/17 17:27:24 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_built_in(t_cmd_lst *lst, t_env_lst *envlst)
{
	if (is_built_in(lst) == TRUE)
	{
		g_exit_code = exec_built_in(lst, envlst, 1);
		return (1);
	}
	return (0);
}

int	exec_ve_abs(t_cmd_lst *lst, t_env_lst *envlst, pid_t pid)
{
	char	**args;

	args = join_args(lst->cmd, lst->args);
	if (execve(lst->cmd, args, lst->envp) == -1)
		g_exit_code = 1;
	return (g_exit_code);
}

int	exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst, pid_t pid)
{	
	char	**path;
	char	**args;
	char	*cmd;
	int		i;

	i = -1;
	path = ft_split(get_env_by_name(envlst, "PATH"), ':');
	if (!path)
		return (1);
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd, lst->cmd);
		args = join_args(cmd, lst->args);
		execve(cmd, args, lst->envp);
	}
	free(args);
	free(path);
	return (g_exit_code);
}

int	exec_ve(t_cmd_lst *lst, t_env_lst *envlst)
{
	pid_t	pid;
	int status;

	if (check_built_in(lst, envlst) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		perror("fork() failed (exec_ve)");
	else if (pid == 0)
	{
		exec_ve_abs(lst, envlst, pid);
		exec_ve_rel(lst, envlst, pid);
		perror("Exec failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("Coordinator: forked and waiting for process %d\n", pid);

        int status;
        if ( waitpid(pid, &status, 0) != -1 ) {
            if ( WIFEXITED(status) ) {
                int returned = WEXITSTATUS(status);
                printf("Exited normally with status %d\n", returned);
            }
            else if ( WIFSIGNALED(status) ) {
                int signum = WTERMSIG(status);
                printf("Exited due to receiving signal %d\n", signum);
            }
            else if ( WIFSTOPPED(status) ) {
                int signum = WSTOPSIG(status);
                printf("Stopped due to receiving signal %d\n", signum);
            }
            else {
                printf("Something strange just happened.\n");
            }
        }
        else {
            perror("waitpid() failed");
            exit(EXIT_FAILURE);
        }
		g_exit_code = status;
	}
	free(lst->cmd);
	free(lst->args);
	return (1);
}
