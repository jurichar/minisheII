/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/28 10:23:55 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/***
 *      __  __ _       _     _          _ _  
 *     |  \/  (_)     (_)   | |        | | | 
 *     | \  / |_ _ __  _ ___| |__   ___| | | 
 *     | |\/| | | '_ \| / __| '_ \ / _ \ | | 
 *     | |  | | | | | | \__ \ | | |  __/ | | 
 *     |_|  |_|_|_| |_|_|___/_| |_|\___|_|_| 
 *                                           
 *                                           
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libft/libft.h"
# include <errno.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdlib.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>

# define TRUE 1
# define FALSE 0
# define SEP ";|"
# define OUT 1
# define OUT_DOUBLE 2
# define IN 3
# define IN_DOUBLE 4

// colors : +10 for background color

# define ZERO "\033[0m"
# define RED "\033[1;31m"
# define GRN "\033[1;32m"
# define YLW "\033[1;33m"
# define BLU "\033[1;34m"
# define MAG "\033[1;35m"
# define CYAN "\033[1;36m"
# define ARROW ">"
# define WILDC 1

int	g_exit_code;

typedef struct s_env_lst
{
	char				*name;
	char				*content;
	int					equal;
	int					len;
	struct s_env_lst	*next;
}				t_env_lst;

typedef struct s_redir
{
	int				redir;
	char			*arg;
	struct s_redir	*next;
}		t_redir;

typedef struct s_tripl
{
	int	x;
	int	y;
	int	z;
}		t_tripl;

typedef struct s_cmd_lst
{
	char				**envp;
	char				*cmd;
	char				**args;
	struct s_redir		*redir;
	char				sep;
	struct s_cmd_lst	*next;
	struct s_cmd_lst	*prev;
	int					fd[2];
	int					nb_p;
	int					builtin;
}			t_cmd_lst;

typedef struct s_fct_params
{
	char				**av;
	struct s_fct_params	*env_list;
}		t_fct_params;

typedef struct s_pipor
{
	int	nbc;
	int	*pid;
	int	tpipes;
	int	*pipes;
}		t_pipor;

typedef struct s_set_line
{
	int	i;
	int	j;
	int	cmd_count;
}				t_set_line;

/*
BUILT IN 
*/
//builtin_init
void		free_point_char(char **str);
void		init_built_in(char **str);
int			is_built_in(t_cmd_lst *lst);

// built_cd
int			builtin_cd_tild(t_env_lst *envlst);
int			builtin_cd(t_cmd_lst *lst, t_env_lst *envlst, int ret);

// built_echo
int			is_n(char *s);
int			builtin_echo(t_cmd_lst *lst, int fd);

// built_env
int			builtin_env(t_env_lst *envlst);

// built_exec
int			exec_built_in(t_cmd_lst *lst, t_env_lst **envlst, int fd);
void		fd_close(int fd[2]);
void		get_built_in(t_cmd_lst **lst, t_env_lst **envlst);

// built_exit
int			builtin_exit( void );

//built_export_tools
void		find_var(t_env_lst **ptr, char *name);
int			valid_identifier(char c, int pos);
int			check_name(char *s);

// built_export_sort
int			env_swap(t_env_lst **c, t_env_lst **p, t_env_lst **b, int i);
t_env_lst	*env_sort(t_env_lst *list, int i);
int			builtin_export_sort(t_env_lst *envlst);

// built_export
int			export_var(char **var, t_env_lst **envlst);
int			export_cat(t_env_lst **list, char *str, char *tmp, char *content);
int			builtin_export(t_cmd_lst *lst, t_env_lst **envlst);

// built_pwd
int			builtin_pwd(void);

// built_unset
int			builtin_unset(t_cmd_lst *lst, t_env_lst **env);

// built_utils
char		**join_args(char *s, char **args);
char		*get_env_by_name(t_env_lst *envlst, char *name);

// ft_execve
int			check_built_in(t_cmd_lst *lst, t_env_lst **envlst);
int			exec_ve_abs(t_cmd_lst *lst);
int			exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst);
int			exec_ve(t_cmd_lst *lst, t_env_lst **envlst);

// ft_pipe
t_pipor		init_pipor(t_cmd_lst *lst);
void		fork_error(t_pipor pip, int i);
void		clean_pid(t_pipor *pip);
int			pipor(t_cmd_lst *lst, t_env_lst *envlst);

// ft_pipe_utils
void		close_pipor(t_pipor *pip);
void		pipor_first(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst);
void		pipor_mid(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst);
void		pipor_last(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst, int i);

// ft_redir
void		ft_redir_in_double(t_cmd_lst *lst);
void		ft_redir_out_double(t_cmd_lst *lst);
void		ft_redir_out(t_cmd_lst *lst);
void		ft_redir_in(t_cmd_lst *lst);
void		ft_redir(t_cmd_lst *lst, t_env_lst *envlst);

/*
MAIN
*/
// cmd_utils
char		*get_cmd(char *s);

// ft_is
int			is_separator(char *s, char c, int pos);
int			is_space(char c);
int			is_sep(char c);
int			is_redir(char *s, char c, int pos);

// env_tools
t_env_lst	*get_env(t_env_lst *list, char **envp);
t_env_lst	*ft_lstnew_env(char *v_name, int equal, char *v_content);

// ft_split_arg
int			args_counter(char *str);
char		*get_cmd_name(char *s, int i, int j, int quote);
void		ft_split_args(char *str, t_cmd_lst **lst, t_env_lst *env);

// ft_split_cmd
int			cmd_counter(char *str, int *pipe, int quote);
void		ft_split_cmd(t_cmd_lst **l, char *s, t_env_lst *env, char **e);

// get_next_line
char		*ft_strndup(char *s, int n);
int			fill_line(char **file_content, char **line);
int			manage_return(char **fc, char **line, int ret, char *buffer);
int			get_next_line(int fd, char **line);

// list_tool
t_cmd_lst	*ft_new_cmd_list(char **envp);
void		ft_env_remove_if(t_env_lst **bl, void *data_ref, int (*cmp)());

// main
void		free_cmds(t_cmd_lst *lst);
void		lst_cmd(char *line, t_env_lst *env, t_cmd_lst **lst, char **envp);
char		*get_line( void );
void		print_point_char(char **str);

// manage_input
void		get_to_cur_pos(int from, int to);
char		*del_char(char *src, int pos);
void		clear_and_print(int len, char *s, int pos);
char		*insert_char(char *start, char c, char *end);

// redir_tools
void		add_redir(t_cmd_lst **lst, char *s, int i);
int			check_redir(char *s);
int			which_redir(char *str);
int			how_many_redir(char *s);

// parse_redir
t_redir		*redir_dup(char *s);
int			skip_redir(char *s, int i);
char		*get_redir(char *s, t_cmd_lst *lst);

// skip
int			skip_space(char *s);

// env_var_manager
char		*insert_env_var(char *str, int i, int quote, t_env_lst *env);
char		*find_env_var(char *str, t_env_lst *env);

// env_var_tools
char		*set_start(char *s, int *quote);
char		*get_ret_value(char *ret, char *s, int quote, int len);

// dup_tools
char		*ft_strdup_sep(char *str);
void		get_line_without_quote(char	*str, char *copy, int len, int quote);
char		*malloc_cmdname(char *s, int *ptr_len);
char		*ft_strdup_space_sep(char *s, t_env_lst *env);

// utils
int			ft_whereis_char(char *s, int c);
char		*ft_strjoin_till_space(char const *s1, char const *s2);
int			get_to_next_quote(char *s, int i);
int			pass_cmd_name(char *s, int i);

// wildcard_tools
char		*ft_strstr(char *str, char *to_find);
int			check_match(char *file, char *wd);
char		*join_words(char **tab, char *res);
char		*insert_match(char *new, char *ptr_begin_wd,
				char *ptr_post_wd, char *wd);
char		*wildcard_found(char *new, char *ptr_begin_wd, int i);

// wildcard
char		*wildcard(char *to_find);
char		*find_wildcard(char *s, char *ptr_begin_wd,
				char *ptr_post_wd, int i);

#endif
