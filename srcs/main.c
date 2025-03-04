/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/11/02 17:26:43 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

void	free_cmds(t_cmd_lst *lst)
{
	void	*nextl;

	if (lst)
	{
		while (lst->next)
		{
			nextl = lst->next;
			free(lst);
			lst = nextl;
		}
		free(lst);
	}
}

void	lst_cmd(char *line, t_cmd_lst **lst, char **envp)
{
	if (line)
		ft_split_cmd(lst, line, envp);
	return ;
}

void	sig_handler(int sig)
{
	if (sig == 3)
	{
		write(1, "\b\b  \b\b", 6);
		return ;
	}
	if (sig == 2)
		write(STDOUT_FILENO, "\n", 1);
	if (isatty(0) && sig != 11)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == 11)
	{
		printf("\b exit\n");
		exit(g_exit_code);
	}
}

char	*get_line(void)
{
	char	*line;

	line = readline("minishell-1.0$ ");
	if (!line)
	{
		sig_handler(11);
	}
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
}

int	main(int ac, char **av, char **env)
{
	t_env_lst	*envlst;
	t_cmd_lst	*lst;
	char		**envp;

	(void) ac;
	(void) av;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_exit_code = 0;
	if (ac != 1 || env == NULL || !env[0])
		return (0);
	envlst = NULL;
	envp = ft_strdoubledup(env);
	envlst = get_env(envlst, envp);
	while (1)
	{
		lst = ft_new_cmd_list(envp);
		lst_cmd(get_line(), &lst, envp);
		if (ft_strcmp(lst->cmd, "NIL") != 0)
			get_built_in(&lst, &envlst, 0);
		ft_free_cmd(lst);
	}
	return (0);
}
