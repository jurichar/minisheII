/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/18 21:32:56 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cmds(t_cmd_lst *lst)
{
	if (lst)
	{
		while (lst->next)
		{
			free(lst);
			lst = lst->next;
		}
		free(lst);
	}
}

void	lst_cmd(char *line, t_env_lst *env, t_cmd_lst **lst, char **envp)
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
		ft_split_cmd(lst, line, env, envp);
	}
	return;
}

char	*get_line( void )
{
	char	*line;
	struct	termios term;

	tcgetattr(0, &term);
	line = ft_strdup("");
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

void no_act_handler(int sig)
{
	// if (sig == 2)
	// {
	// 	printf("\b\b");
	// 	printf(BLU ARROW ZERO);
	// 	printf("\n");
	// }
	if (sig == 11)
	{
		printf("\b\bexit");
		exit(g_exit_code);
	}
	return;
}

int		main(int ac, char **av, char **envp)
{
	t_env_lst *envlst;
	t_cmd_lst *lst;
	(void) ac;
	(void) av;
	signal(SIGINT, no_act_handler);
	signal(SIGSEGV, no_act_handler);
	signal(SIGQUIT, no_act_handler);
	g_exit_code = 0;
	if (ac != 1 || envp == NULL)
		return 0; 
	lst = NULL;
	lst = ft_new_cmd_list(envp);
	envlst = NULL;
	envlst = get_env(envlst, envp);
	while (1)
	{
		// if ( waitpid(pid, NULL, 0) != -1 )
		lst_cmd(get_line(), envlst, &lst, envp);
		if (ft_strcmp(lst->cmd, "NIL") != 0)
		{
			get_built_in(&lst, envlst);
			lst = ft_new_cmd_list(envp);
		}
	}
	return (0);
 }
