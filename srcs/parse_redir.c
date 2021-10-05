/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 15:40:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/24 21:14:35 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_redir(char *s, int pos, t_redir **new)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (s[pos])
	{
		if (quote == 0 && (s[pos] == '\'' || s[pos] == '"'))
		{
			quote = get_to_next_quote(s, pos);
			pos++;
			continue ;
		}	
		if (quote && pos == quote)
		{
			pos++;
			quote = 0;
			continue ;
		}	
		if (quote == 0 && is_space(s[pos]))
			break ;
		(*new)->arg = ft_realloc((*new)->arg, ft_strlen((*new)->arg));
		(*new)->arg[i++] = s[pos++];
	}
	(*new)->next = NULL;
}

/*
**REDIR_DUP
**
**Allocate a new redirection list element. Also store the redirection type in
**new->redir and the file name in new->arg
*/
t_redir	*redir_dup(char *s)
{
	int			start;
	int			pos;
	t_redir		*new;

	start = 0;
	new = malloc(sizeof(t_redir));
	new->redir = which_redir(s);
	while (s[start] && (s[start] == '>' || s[start] == '<'))
		start++;
	start += skip_space(&s[start]);
	pos = start;
	new->arg = ft_realloc(NULL, 0);
	set_redir(s, pos, &new);
	return (new);
}

/*SKIP_REDIR
**
**return the index of the character next to the end of a redirection file name
*/
int	skip_redir(char *s, int i)
{
	if (s[i] == '>')
	{
		while (s[i] && s[i] == '>')
			i++;
		if (i == 3 || s[i] == '\0' || s[i] == '<')
			return (-1);
	}
	else if (s[i] == '<')
	{
		while (s[i] && s[i] == '<')
			i++;
		if (i == 3 || s[i] == '\0' || s[i] == '>')
			return (-1);
	}
	while (s[i] && is_space(s[i]))
		i++;
	if (s[i] == '\0')
		return (-1);
	while (ft_isalnum(s[i]))
		i++;
	if (s[i] == '\'' || s[i] == '"')
		i = get_to_next_quote(s, i) + 1;
	while (ft_isalnum(s[i]))
		i++;
	return (i);
}

char	*get_line_without_redir(char *s, t_cmd_lst *lst)
{
	
}

/*
**GET_REDIR
**
**New will store a string that cointain the s string without the redirections
**while allocating n list->redir with redir_dup and storing inside the structure
**all the redirection information
*/
char	*get_redir(char *s, t_cmd_lst *lst)
{
	char	*new;
	t_redir	*begin;
	int		len;
	int		i;

	len = check_redir(s);
	new = malloc(sizeof(char) * (len + 1));
	begin = NULL;
	i = -1;
	len = 0;
	while (s[++i])
	{
		if (is_redir(s, s[i], i))
		{
			if (begin == NULL)
			{
				lst->redir = redir_dup(&s[i]);
				begin = lst->redir;
			}
			else
			{
				lst->redir->next = redir_dup(&s[i]);
				lst->redir = lst->redir->next;
			}
			i = skip_redir(s, i);
		}
		new[len] = s[i];
		len++;
	}
	lst->redir = begin;
	new[len] = '\0';
	return (new);
}
