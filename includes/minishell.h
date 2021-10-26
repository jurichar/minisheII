/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/26 15:18:37 by jurichar         ###   ########.fr       */
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
# define OR 1
# define AND 2

extern int	g_exit_code;

typedef struct s_env_lst
{
	char				*name;
	char				*content;
	int					visible;
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
	int					phlvl;
	int					sep_phlvl;
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

typedef struct s_tripl
{
	int	x;
	int	y;
	int	z;
}		t_tripl;

typedef struct s_set_line
{
	int	i;
	int	j;
	int	cmd_count;
	int	phlvl;
}				t_set_line;

typedef struct s_pth_var
{
	int	qt;
	int	sts;
}				t_pth_var;

/*
BUILT IN
*/
// built_cd_home
int			built_cd_home(t_env_lst **envlst, int ret);

// built_cd
int			builtin_cd_tild(t_env_lst *envlst);
int			builtin_cd(t_cmd_lst *lst, t_env_lst **envlst, int ret);

// built_echo
int			is_n(char *s);
int			builtin_echo(t_cmd_lst *lst, int fd);

// built_env
int			builtin_env(t_env_lst *envlst);

// built_exit
int			builtin_exit(t_cmd_lst *lst, t_env_lst *envlst);

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

//builtin_init
void		free_point_char(char **str);
void		init_built_in(char **str);
int			is_built_in(t_cmd_lst *lst);

/*
EXEC
*/

// built_exec
int			exec_built_in(t_cmd_lst *lst, t_env_lst **envlst, int fd);
void		fd_close(int fd[2]);
void		get_built_in(t_cmd_lst **lst, t_env_lst **envlst, int i);

// ft_execve
int			check_built_in(t_cmd_lst *lst, t_env_lst **envlst);
int			exec_ve_abs(t_cmd_lst *lst, t_env_lst *envlst);
int			exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst);
int			exec_ve(t_cmd_lst *lst, t_env_lst **envlst);

// ft_pipe_utils
void		close_pipor(t_pipor *pip);
void		pipor_first(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst);
void		pipor_mid(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst);
void		pipor_last(t_pipor pip, t_cmd_lst *lst, t_env_lst *envlst, int i);

// ft_pipe
t_pipor		init_pipor(t_cmd_lst *lst);
void		fork_error(t_pipor pip, int i);
void		clean_pid(t_pipor *pip);
int			pipor(t_cmd_lst *lst, t_env_lst *envlst);

// ft_redir
void		ft_redir_in_double(t_cmd_lst *lst);
void		ft_redir_out_double(t_cmd_lst *lst);
void		ft_redir_out(t_cmd_lst *lst);
int			ft_redir_in(t_cmd_lst *lst);
int			ft_redir(t_cmd_lst *lst, t_env_lst *envlst);

/*
SRCS
*/

// cmd_utils
void		init_var_cmd(t_set_line *var, char *str, t_cmd_lst *lst_begin);
int			which_sep(char *str, int i);
char		*clear_parenthesis(char *s);
char		*get_cmd(char *s);

// dup_tools
char		*ft_strdup_sep(char *str);
void		get_line_without_quote(char	*str, char *copy, int len, int quote);
char		*malloc_cmdname(char *s, int *ptr_len);
char		*ft_strdup_space_sep(char *s, int quote);

// env_tools
t_env_lst	*get_env(t_env_lst *list, char **envp);
t_env_lst	*ft_lstnew_env(char *v_name, int equal, char *v_content);

// env_tools2
void		check_oldpwd(t_env_lst **begin);

// env_var_manager
char		*insert_env_var(char *str, int i, t_env_lst *env, int squote);
char		*find_env_var(char *str, t_env_lst *env, int i);

// env_var_tools
char		*set_start(char *s, int *quote);
char		*get_ret_value(char *ret, char *s, int quote, int len);

// expand
void		expand_before_exec(t_cmd_lst **lst, t_env_lst *envlst, int j);

// ft_free
void		ft_free_env(t_env_lst *lst);
void		ft_free_cmd(t_cmd_lst *lst);

// ft_is
int			is_separator(char *s, char c, int pos);
int			is_space(char c);
int			is_sep(char c);
int			is_redir(char *s, char c, int pos);

// ft_split_arg
int			args_counter(char *str);
char		*get_cmd_name(char *s, int i, int j, int quote);
void		ft_split_args(char *str, t_cmd_lst **lst);

// ft_split_cmd
int			cmd_counter(char *str, int *pipe, int quote);
void		ft_split_cmd(t_cmd_lst **l, char *s, char **e);

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
void		lst_cmd(char *line, t_cmd_lst **lst, char **envp);
char		*get_line( void );
void		print_point_char(char **str);
void		sig_handler(int sig);

// manage_input
void		get_to_cur_pos(int from, int to);
char		*del_char(char *src, int pos);
void		clear_and_print(int len, char *s, int pos);
char		*insert_char(char *start, char c, char *end);

// parenthesis
int			check_parenthesis(char *s);

// parenthesis2
int			check_empty_pth(char *s);
int			check_back_pth(char *s, int i, int pth_nb, int status);
int			check_front_pth(char *s, int i, int pth_nb, int inside);
int			check_fist_last_pth(char *s);

// parse_redir
t_redir		*redir_dup(char *s);
int			skip_redir(char *s, int i);
char		*get_redir(char *s, t_cmd_lst *lst);

// pth_utils
int			init_pth_var_check_s(t_pth_var *var, char *s, int i);

// quote
int			double_quote_status(int quote, int i, char *s);
int			quote_status(int quote, int i, char *s);
int			get_to_next_quote(char *s, int i);

// redir_tools
void		add_redir(t_cmd_lst **lst, char *s, int i);
int			check_redir(char *s);
int			which_redir(char *str);
int			how_many_redir(char *s);

// skip
int			skip_space(char *s);

// update_envp
int			get_env_size(t_env_lst *lst);
char		**update_envp(t_env_lst *lst, int size_env);

// utils
int			print_and_ret(char *to_print, int to_ret);
int			ft_whereis_char(char *s, int c);
char		*ft_strjoin_till_space(char const *s1, char const *s2);
int			pass_cmd_name(char *s, int i);
char		*malloc_line(char *str, int *ptr_len);

// wildcard_tools
char		*ft_strstr(char *str, char *to_find);
int			check_match(char *file, char *wd);
char		*join_words(char **tab, char *res);
char		*insert_match(char *new, char *ptr_begin_wd,
				char *ptr_post_wd, char *wd);
char		*wildcard_found(char *new, char *ptr_begin_wd, int i);

// wildcard
char		*wildcard(char *to_find);
char		*find_wildcard(char *s, char *ptr_begin_wd, int i);

#endif
