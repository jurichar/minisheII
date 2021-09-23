/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/23 11:29:13 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	lst_cmd(char *line, t_env_lst *env, t_cmd_lst **lst, char **envp)
{
	if (line)
	{
	//	check_line(line);
		ft_split_cmd(lst, line, env, envp);
	}
	return ;
}

void	sig_handler(int sig)
{
	g_exit_code = 128 + sig;
	write(STDOUT_FILENO, "\n", 1);
	if (isatty(0))
	{
		rl_on_new_line();
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	if( sig== 11)
	{
		printf ("\b\bexit\n");
		exit(g_exit_code);
	}
}

char	*get_line( void )
{
	char	*line;

	line = readline("minishell-1.0$ ");
	if (ft_strlen(line) > 0)
		add_history(line);
	return (line);
	// char	*ret;

	// while (1)
	// {
		// printf ("coucou");

	(void) ac;
	(void) av;
	
	signal(SIGINT, sig_handler);
	signal(SIGSEGV, sig_handler);
	signal(SIGQUIT, sig_handler);
	g_exit_code = 0;
	if (ac != 1 || envp == NULL)
		return (0);
	lst = NULL;
	lst = ft_new_cmd_list(envp);
	envlst = NULL;
	envlst = get_env(envlst, envp);
	while (1)
	{
		lst_cmd(get_line(), envlst, &lst, envp);
		if (ft_strcmp(lst->cmd, "NIL") != 0)
		{
			get_built_in(&lst, &envlst);
			lst = ft_new_cmd_list(envp);
		}
	}
	return (0);
}
