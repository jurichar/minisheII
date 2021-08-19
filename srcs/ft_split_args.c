/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 11:56:25 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/18 01:21:10 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	print_hex(char c)
{
	char *hex;

	hex = "0123456789abcdef";
	ft_putchar('\\');
	ft_putchar(hex[(unsigned char)c / 16]);
	ft_putchar(hex[(unsigned char)c % 16]);
}

void	ft_putstr_non_printable(char *str)
{
	while (*str)
	{
		if (*str >= ' ' && *str <= '~')
			ft_putchar(*str);
		else
			print_hex(*str);
		str++;
	}
}

char	*get_arg(char *s, t_env_lst *env, int slash)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		quote;
	int		end_quote;

	(void)slash;
	quote = 0;
	if (s[0] == '"')
	{
		s++;
		quote = 1;
	}
	s++;
	len = 0;
	end_quote = 0;
	while (s[len] && !is_sep(s[len]) && !is_space(s[len])
		&& s[len] != '\\' && s[len] != '"' && s[len] != '\'' && s[len] != '/')
	{
		len++;
	}
	ret = ft_substr(s, 0, len);
	if ((ft_strcmp(ret, "?") == 0))
	{
		tmp = ret;
		ret = ft_strjoin(ft_itoa(g_exit_code), &s[len]);
		free(tmp);
		return (ret);
	}
	if (s[len] == '\0' || (s[len] == '"' && quote == 1))
		return (ret);
	while (env && (ft_strcmp(ret, env->name) != 0))
		env = env->next;
	if (env != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(env->content, &s[len]);
		free(tmp);
	}
	else
	{
		free(ret);
		return (&s[len]);
	}
	return (ret);
}

char	*ft_strdup_space_sep(char *s, t_env_lst *env)
{
	int		i;
	int		j;
	int		lenght;
	int		quote;
	char	*copy;
	char	*str;
	char	*var;

	lenght = -1;
	i = -1;
	quote = 0;
	str = ft_strdup(s);
	while (str[++i] && !is_sep(str[i]))
	{
		if ((str[i] == '"' && str[i + 1] == '$') || str[i] == '$')
		{
			var = get_arg(&str[i], env, 0);
			str = ft_substr(str, 0, i);
			copy = str;
			str = ft_strjoin(str, var);
			free(copy);
		}
		else if (lenght == 0 && (str[lenght] == '\'' || str[lenght] == '"'))
		{
			quote = 1;
			j = get_to_next_quote(str, lenght);
		}
		if (quote == 0 && is_space(str[lenght]))
			break ;
		else if (quote == 1 && lenght == j && str[lenght + 1] == ' ')
			break ;
		else if (quote == 1 && lenght == j && str[lenght + 1] != ' ')
		{
			while (ft_isalnum(str[++lenght]))
				i++;
			break ;
		}
		if ((str[lenght + 1] == '\'' || str[lenght + 1] == '"')
		&& str[lenght] == '\\')
			lenght += 2;
	}
	if (!(copy = malloc(sizeof(char) * lenght + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (++i < lenght)
	{
		if (str[i] == '\\' && str[i - 1] != '\\')
			copy[j++] = str[i++ + 1];
		if (!(str[i] == '\'' || str[i] == '"'))
			copy[j++] = str[i];
	}
	copy[j] = '\0';
	return (copy);
}

int		args_counter(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 1;
	i = pass_cmd_name(str, i);
	while (str[i] && !is_sep(str[i + 1]))
	{
		if (str[i - 1] == ' ' && (str[i] == '\'' || str[i] == '"'))
		{
			i = get_to_next_quote(str, i);
			count++;
		}
		else if (!is_space(str[i])
		&& (is_space(str[i + 1]) || str[i + 1] == '\0' || is_sep(str[i + 1])))
			count++;
		i++;
	}
	return (count);
}

char	*get_cmd_name(char *s)
{
	int		i;
	int		len;
	char	*cmd;

	len = 0;
	i = 0;
	while (s[i] && is_space(s[i]))
		i++;
	while (s[i] && !is_space(s[i]))
	{
		len++;
		i++;
	}
	cmd = malloc(sizeof(char) * (len + 1));
	i = skip_space(s);
	len = 0;
	while (s[i] && !is_space(s[i]))
	{
		cmd[len] = s[i];
		i++;
		len++;
	}
	cmd[len] = '\0';
	return (cmd);
}

void	ft_split_args(char *str, t_cmd_lst **lst, t_env_lst *env)
{
	char	*tmp;
	int		args_count;
	int		i;
	int		j;

	if (how_many_redir(str) > 0)
	{
		tmp = get_redir(str, *lst);
		free(str);
		str = tmp;
	}
	args_count = args_counter(str);
	(*lst)->args = malloc(sizeof(char *) * (args_count + 1));
	i = 0;
	j = 0;
	while (is_space(str[j]) && str[j])
		j++;
	(*lst)->cmd = get_cmd_name(&str[j]);
	while (!is_space(str[j]) && str[j])
			j++;
	while (++i < args_count)
	{
		while (str[j] && is_space(str[j]))
			j++;
		(*lst)->args[i - 1] = ft_strdup_space_sep(&str[j], env);
		if (str[j] == '\'' || str[j] == '"')
			j = get_to_next_quote(str, j);
		while (!is_space(str[j]) && str[j])
			j++;
	}
	(*lst)->args[i - 1] = NULL;
}