/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:05:17 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/18 02:08:22 by jurichar         ###   ########.fr       */
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
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <termios.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

# define SEP ";|"
// colors : +10 for background color

# define ZERO "\033[0m"
# define RED "\033[1;31m"
# define GRN "\033[1;32m"
# define YLW "\033[1;33m"
# define BLU "\033[1;34m"
# define MAG "\033[1;35m"
# define CYAN "\033[1;36m"
# define ARROW ">"//"\u1405"

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
    int x;
	int y;
	int z;
} t_tripl;

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
}				t_cmd_lst;

typedef struct s_fct_params
{
	char				**av;
	struct s_fct_params	*env_list;
}				t_fct_params;

/*
BUILT IN 
*/
// built_cd
int	builtin_cd_tild(t_env_lst *envlst);
int	builtin_cd(t_cmd_lst *lst, t_env_lst *envlst, int ret);
// built_echo
int	is_n(char *s);
int	builtin_echo(t_cmd_lst *lst, int fd);
// built_env
int	builtin_env(t_env_lst *envlst);
// built_exec
int	exec_built_in(t_cmd_lst *lst, t_env_lst *envlst, int fd);
int	is_built_in(t_cmd_lst *lst);
void	fd_close(int fd[2]);
void	get_built_in(t_cmd_lst **lst, t_env_lst *envlst);
// built_exit
int	builtin_exit( void );

// built_export_sort
int			env_swap(t_env_lst **curr, t_env_lst **prev, t_env_lst **begin, int i);
t_env_lst	*env_sort(t_env_lst *list, int i);
int			builtin_export_sort(t_env_lst *envlst);

// built_export
int	valid_identifier(char c, int pos);
int	check_name(char *s);
int		export_var(char **var, t_env_lst **envlst);
int		builtin_export(t_cmd_lst *lst, t_env_lst *envlst);

// built_pwd
int	builtin_pwd();
// built_unset
int	builtin_unset(t_cmd_lst *lst, t_env_lst *env);
// built_utils
char	**join_args(char *s, char **args);
char	*get_env_by_name(t_env_lst *envlst, char *name);
// ft_execve
int	check_built_in(t_cmd_lst *lst, t_env_lst *envlst);
int	exec_ve_abs(t_cmd_lst *lst);
int	exec_ve_rel(t_cmd_lst *lst, t_env_lst *envlst);
int	exec_ve(t_cmd_lst *lst, t_env_lst *envlst);
// ft_pipe
int	forkito(int in, int out, t_cmd_lst *lst, t_env_lst *envlst);
int	pipor(t_cmd_lst *lst, t_env_lst *envlst);
// ft_redir
void	ft_redir_in_double(t_cmd_lst *lst, t_env_lst *envlst);
void	ft_redir_out_double(t_cmd_lst *lst);
void	ft_redir_out(t_cmd_lst *lst);
void	ft_redir_in(t_cmd_lst *lst);
void	ft_redir(t_cmd_lst *lst, t_env_lst *envlst);

// safe export
t_env_lst	*env_sort(t_env_lst *list, int i);
int	builtin_export(t_cmd_lst *lst, t_env_lst *envlst);

/*
MAIN
*/
// cmd_utils
char	*get_cmd(char *s);

// ft_is
int	is_space(char c);
int	is_sep(char c);
int	is_redir(char *s, int i);

// ft_lstnew_env
t_env_lst		*ft_lstnew_env(char *v_name, int equal, char *v_content);

// ft_split_arg
void	ft_putchar(char c);
void	print_hex(char c);
void	ft_putstr_non_printable(char *str);
char	*get_arg(char *s, t_env_lst *env, int slash);
char	*ft_strdup_space_sep(char *str, t_env_lst *env);
int		args_counter(char *str);
char	*get_cmd_name(char *s);
void	ft_split_args(char *str, t_cmd_lst **lst, t_env_lst *env);

// ft_split_cmd
int		is_separator(char c, char *separator);
char	*ft_strdup_sep(char *str, char *separator);
int		cmd_counter(char *str, char *separator, int *pipe);
void	ft_split_cmd(t_cmd_lst **lst, char *str, t_env_lst *env, char **envp);

// get_next_line
char	*ft_strndup(char *s, int n);
int		fill_line(char **file_content, char **line);
int		manage_return(char **file_content, char **line, int ret, char *buffer);
int		get_next_line(int fd, char **line);

// historic
int		historic_size(void);
char	*get_historic(int up);

// list_tool
t_cmd_lst	*ft_new_cmd_list(char **envp);
void	ft_env_remove_if(t_env_lst **begin_list, void *data_ref, int (*cmp)());
// main
void	free_cmds(t_cmd_lst *lst);
void	lst_cmd(char *line, t_env_lst *env, t_cmd_lst **lst, char **envp);
char	*get_line( void );
void print_point_char(char **str);
// manage_input
void	get_to_cur_pos(int from, int to);
char	*del_char(char *src, int pos);
void	clear_and_print(int len, char *s, int pos);
char	*insert_char(char *start, char c, char *end);
// parse_redir
int	how_many_redir(char *s);
int	which_redir(char *str);
t_redir	*redir_dup(char *s);
int	skip_redir(char *s);
char	*get_redir(char *s, t_cmd_lst *lst);
// set canonic
void set_term_ncan(void);
void set_term_can(struct termios term);
// skip
int	skip_space(char *s);
// utils
int		ft_whereis_char(char *s, int c);
char	*ft_strjoin_till_space(char const *s1, char const *s2);
int		get_to_next_quote(char *s, int i);
int		pass_cmd_name(char *s, int i);
t_env_lst	*get_env(t_env_lst *list, char **envp);

#endif
