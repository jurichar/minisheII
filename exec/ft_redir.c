/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:41:02 by jurichar          #+#    #+#             */
/*   Updated: 2021/10/27 19:39:21 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void 	sigito(int sig)
{
	write(1, "\n", 1);
	exit(130);
}

void	ft_redir_in_double(t_cmd_lst *lst)
{
	int		fd0;
	int		fd;
	char	*line;
	pid_t pid;


	line = ft_strjoin("libft/.", lst->redir->arg);
	fd0 = open(line, O_CREAT | O_RDWR | O_TRUNC, 0666);
	free(line);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		perror("fork() failed (exec_ve)");
	else if (pid == 0)
	{
		while (1)
		{
		signal(SIGINT, sigito);
		line = readline("> ");
		if (ft_strcmp(line, lst->redir->arg) == 0 || !line) 
			exit (0) ;
		ft_putstr_fd(line, fd0);
		ft_putstr_fd("\n", fd0);
		}
	}
	else
		exec_error(pid);
	close(fd0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	line = ft_strjoin("libft/.", lst->redir->arg);
	printf("exit code = %d\n", g_exit_code);
	if (g_exit_code != 130)
	{
	fd = open(line, O_RDWR, 0666);
	free(line);
	dup2(fd, 0);
	close(fd);
	}
}

void	ft_redir_out_double(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_CREAT | O_RDWR | O_APPEND, 0666);
	dup2(fd, 1);
	close(fd);
}

void	ft_redir_out(t_cmd_lst *lst)
{
	int		fd;
	char	*file;

	file = lst->redir->arg;
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0666);
	dup2(fd, 1);
	close(fd);
}

int	ft_redir_in(t_cmd_lst *lst)
{
	int	fd;

	fd = open(lst->redir->arg, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst->redir->arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (0);
	}
	else
	{
		dup2(fd, 0);
		close(fd);
		return (1);
	}
}

int	ft_redir(t_cmd_lst *lst, t_env_lst *envlst)
{
	int	i;

	i = TRUE;
	if (lst->redir->redir == OUT)
		ft_redir_out(lst);
	else if (lst->redir->redir == OUT_DOUBLE)
		ft_redir_out_double(lst);
	else if (lst->redir->redir == IN)
		i = ft_redir_in(lst);
	else if (lst->redir->redir == IN_DOUBLE)
		ft_redir_in_double(lst);
	if (lst->sep == '|')
		pipor(lst, envlst);
	if (lst->redir->next)
	{
		lst->redir = lst->redir->next;
		ft_redir(lst, envlst);
	}
	return (i);
}
