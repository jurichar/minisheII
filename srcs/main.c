/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/17 22:47:06 by jurichar         ###   ########.fr       */
=======
/*   Updated: 2021/08/17 19:30:52 by jurichar         ###   ########.fr       */
>>>>>>> origin/master2
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmds(t_cmd_lst *lst)
{
	int i;
	int j;

	if (lst)
	{
		i = -1;
		while (lst->next)
		{
			free(lst);
			lst = lst->next;
		}
		free(lst);
	}
}

void	print_cmd(t_cmd_lst *lst)
{
	int i;
	int j;

	if (!lst)
		return ;
	i = -1;
	while (lst)
	{
		printf("> commande avec ses args respectif:\n> %s\n>\n", lst->cmd);
		lst = lst->next;
	}
}

t_cmd_lst	*lst_cmd(char *line, t_env_lst *env, char **envp)
{
	t_cmd_lst	*lst;
	int		fd;
	char	*tmp;

	lst = NULL;
	if (*line && line)
	{
		tmp = get_historic(1);
		if ((ft_strcmp(tmp, line)) != 0)
		{
			fd = open("./historic", O_WRONLY|O_CREAT|O_APPEND);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			close(fd);
		}
		ft_split_cmd2(&lst, line, env, envp);
		//free(line);
	}
	return (lst);
}

void	lst_cmd2(char *line, t_env_lst *env, t_cmd_lst **lst, char **envp)
{
	int		fd;
	char	*tmp;

	fd = 0;
	if (*line && line)
	{
		tmp = get_historic(1);
		if ((ft_strcmp(tmp, line)) != 0)
		{
			fd = open("./historic", O_WRONLY|O_CREAT|O_APPEND, 0655);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			close(fd);
		}
		ft_split_cmd2(lst, line, env, envp);
	}
	return;
}

char	*get_line(int up)
{
	char	*line;
	struct	termios term;
	char	buf;
	int		len;
	int		cur_pos;
	char	*tmp;

	tcgetattr(0, &term);
	line = ft_strdup("");
	len = 0;
	cur_pos = 0;
	line = readline(BLU ARROW" "ZERO);
	add_history(line);
	return (line);
}

void print_point_char(char **str)
{
	int i = -1;
	while (str[++i])
		ft_putstr_fd(str[i], 1);
}

void  INThandler(int sig)
{
	if (sig == 3)
	{
		printf ("signal SIGQUIT\n");
		exit(g_exit_code);
	}
	if (sig == 2)
	{
		printf ("^C\n");
		kill(getpid(), 2);
		exit(g_exit_code);
	}
	if (sig == 11)
	{
		exit(g_exit_code);
	}
}

int		main(int ac, char **av, char **envp)
{
	t_env_lst *envlst;
	t_cmd_lst *lst;

	g_exit_code = 0;
	if (ac != 1 || envp == NULL)
		return 0; 
	lst = NULL;
	lst = ft_new_cmd_list(envp);
	envlst = NULL;
	envlst = get_env(envlst, envp);
	while (1)
	{
		// signal(SIGSEGV, INThandler);
		// //signal(SIGINT, INThandler);
		// signal(SIGQUIT, INThandler);
		//lst = lst_cmd(get_line(0, db), envlst); // ok
		lst_cmd2(get_line(0), envlst, &lst, envp); // ok
		// print_cmd(lst);
		if (ft_strcmp(lst->cmd, "NIL") != 0)
		{
			get_built_in(&lst, envlst, envp);
			// free(lst);
			lst = ft_new_cmd_list(envp);
		}
	}
	return (0);
} // faut mute les touches qu on a pas le droit de use genre TAB
