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


int	how_many_redir(char *s)
{
	int		i;
	int		count;
	int		quote;

	i = -1;
	count = 0;
	quote = 0;
	while (s[++i])
	{
		if (quote == 0 && is_sep(s[i]))
			break ;
		if (quote == 0 && (s[i] == '\'' || s[i] == '"'))
			quote = get_to_next_quote(s, i);
		if (quote && quote == i)
			quote = 0;
		if (quote == 0 && (s[i] == '>' || s[i] == '<'))
		{
			if ((s[i] == '>' && s[i + 1] == '>')
				|| (s[i] == '<' && s[i + 1] == '<'))
				i++;
			count++;
		}
	}
	printf("count == %d\n", count);
	return (count);
}

int	which_redir(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '<')
			return (4);
		else
			return (1);
	}
	else if (str[0] == '>')
	{
		if (str[1] ==  '>')
			return (3);
		else
			return (2);
	}
	else
		return (0);
}


/*
**REDIR_DUP
**
**Allocate a new redirection list element. Also store the redirection type in
**new->redir and the file name in new->arg
*/
t_redir	*redir_dup(char *s)
{
	int			i;
	int			start;
	int			pos;
	t_redir		*new;
	int			quote;

	start = 0;
	new = malloc(sizeof(t_redir));
	new->redir = which_redir(s);
	while (s[start] && (s[start] == '>' || s[start] == '<'))
		start++;
	start += skip_space(&s[start]);
	pos = start;
	quote = 0;
	i = 0;
	new->arg = ft_realloc(NULL, 0);
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
		new->arg = ft_realloc(new->arg, ft_strlen(new->arg));
		new->arg[i++] = s[pos++];
	}
	//new->arg = ft_substr(s, start, pos - 1);
	// printf("redir = %s.\n", new->arg);
	new->next = NULL;
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
	t_redir *begin;
	int		len;
	int		i;

	len = 0;
	i = -1;
	while (s[++i])
	{
		if (is_redir(s, s[i], i))
			i = skip_redir(s, i);
		if (i == -1)
			return ("syntax error\n");
		len++;
	}
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