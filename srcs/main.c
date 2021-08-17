/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 10:50:02 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/05 16:31:16 by jurichar         ###   ########.fr       */
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

char	*get_line(int up, int db)
{
	char	*line;
	struct	termios term;
	char	buf;
	int		len;
	int		cur_pos;
	char	*tmp;

	tcgetattr(0, &term);
	line = ft_strdup("");
	//set_term_ncan();
	len = 0;
	cur_pos = 0;
	ft_putstr_fd(BLU ARROW" " ZERO, 1);
	line = readline(NULL);
	add_history(line);
	/*
	while (1)
	{
		read(STDIN_FILENO, &buf, 1);
		if (buf == 10) // return
		{
			write(1, "\n", 1);
			break ;
		}
		else if (buf == 27) // esc
		{
			read(STDIN_FILENO, &buf, 1);
			if (buf == '[')
			{
				read(STDIN_FILENO, &buf, 1);
				if (buf == 'D' && cur_pos > 0)
				{
					ft_putstr_fd("\b", 1);
					cur_pos--;
				}
				else if (buf == 'C' && cur_pos < len)
				{
					ft_putstr_fd("\e[1C", 1);
					cur_pos++;
				}
				else if (buf == 'A' && up < historic_size())
				{
					len = ft_strlen(line);
					free(line);
					up++;
					line = get_historic(up);
//					printf("hist = %s\tcur_pos = %d\n", line, cur_pos);
					clear_and_print(len, line, cur_pos);
					cur_pos = ft_strlen(line);
					len = cur_pos;
//`					printf("\tcur_pos = %d\n", cur_pos);
				}
				else if (buf == 'B' && up != 0)
				{
					len = ft_strlen(line);
					free(line);
					up--;
					line = get_historic(up);
					clear_and_print(len, line, cur_pos);
					cur_pos = ft_strlen(line);
					len = cur_pos;
				}
			}
		}
		else if (buf == 127)  // del
		{
			if (cur_pos > 0)
			{
				line = del_char(line, cur_pos);
				clear_and_print(len, line, cur_pos);
				write(1, " \b", 2);
				cur_pos--;
				get_to_cur_pos(ft_strlen(line), cur_pos);
				len--;
			}
			if (cur_pos > 0)
			{
				ft_putstr_fd("\b \b", 1);
				line = del_char(line, cur_pos);
				len--;
				cur_pos--;
			}
//			printf("\nline = %s\n", line);
		}
		else if (buf == 3) // ctrl + c
		{
			set_term_can(term);
			exit(0);
		}
		else
		{
			if (cur_pos == len)
			{
				write(1, &buf, 1);
				line = ft_realloc(line, len + 1);
				line[len] = buf;
				len++;
				cur_pos++;
			}
			else
			{
				tmp = insert_char(ft_substr(line, 0, cur_pos),
buf, ft_substr(line, cur_pos, ft_strlen(line) - cur_pos));
				free(line);
				line = ft_strdup(tmp);
				cur_pos = ft_strlen(line);
				clear_and_print(len, line, cur_pos);
			}
		}
//		printf("buf = %c\n", buf);
//		printf("line = %s len = %lu\n", line, ft_strlen(line));
	}
	*/
	//set_term_can(term);
	if (db == 1)
		printf(YLW "line =" ZERO " %s\n", line);
	return (line);
}

void print_point_char(char **str)
{
	int i = -1;
	while (str[++i])
		ft_putstr_fd(str[i], 1);
}

int		main(int ac, char **av, char **envp)
{
	t_env_lst *envlst;
	t_cmd_lst *lst;
	int db;

	g_exit_code = 0;
	if (ac != 1 || envp == NULL)
		return 0; 
	lst = NULL;
	lst = ft_new_cmd_list(envp);
	envlst = NULL;
	envlst = get_env(envlst, envp);
	while (1)
	{
		//lst = lst_cmd(get_line(0, db), envlst); // ok
		lst_cmd2(get_line(0, db), envlst, &lst, envp); // ok
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
