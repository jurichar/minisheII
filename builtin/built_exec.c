/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:30:10 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/10 18:03:01 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_tripl	tripl_init(void)
{
	t_tripl	tripl;

	tripl.x = -1;
	tripl.y = 0;
	tripl.z = FALSE;

	return (tripl);
}

int	is_built_in(t_cmd_lst *lst)
{
	char	**builtin_list;
	t_tripl	tripl;

	// tripl = tripl_init();
	tripl.x = 0;
	tripl.y = 0;
	tripl.z = FALSE;
	builtin_list = malloc(sizeof(char *) * 9);
	if (!builtin_list)
		return (0);
	builtin_list[0] = ft_strdup("cd");
	builtin_list[1] = ft_strdup("echo");
	builtin_list[2] = ft_strdup("pwd");
	builtin_list[3] = ft_strdup("export");
	builtin_list[4] = ft_strdup("unset");
	builtin_list[5] = ft_strdup("env");
	builtin_list[6] = ft_strdup("exit");
	builtin_list[7] = "\0";
	while (tripl.x <= 7)
	{
		tripl.y = ft_strcmp(builtin_list[tripl.x], lst->cmd);
		if (tripl.y == FALSE)
		{
			tripl.z = TRUE;
			break ;
		}
		tripl.x++;
	}
	free(builtin_list);
	return (tripl.z);
}

void	fd_close(int fd[2])
{
	dup2(fd[0], 0);
	if (fd[0] != 1)
		close(fd[0]);
	dup2(fd[1], 1);
	if (fd[1] != 1)
		close(fd[1]);
}

void	get_built_in(t_cmd_lst **lst, t_env_lst *envlst, char **envp)
{
	int		builtin;
	int		fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (!lst)
		return ;
	while (lst)
	{
		if ((*lst)->redir != NULL)
		{
			ft_redir(*lst, envlst);
			exec_ve(*lst, envlst);
		}
		else if ((*lst)->sep == '|')
			pipor(*lst, envlst);
		else
			exec_ve(*lst, envlst);
		fd_close(fd);
		break ;
	}
	fd_close(fd);
}
