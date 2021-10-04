/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:19:26 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/04 18:19:28 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

char    *set_start(char *s, int *quote)
{
    *quote = 0;
    if (s[0] == '"')
    {
        *quote = get_to_next_quote(s, 0);
        if (!s[*quote])
            *quote = 0;
        else
            s++;
    }
    s++;
    return (s);
}

char    *get_ret_value(char *ret, char *s, int quote, int len)
{
    char    *tmp;

	tmp = ret;
	ret = ft_strjoin(ft_itoa(g_exit_code), &s[len]);
	free(tmp);
	if (quote == 1)
	{
		tmp = ret;
		ret = ft_strjoin("\"", tmp);
		free (tmp);
	}
	return (ret);
}

char	*get_arg(char *s, t_env_lst *env)
{
	char	*ret;
	char	*tmp;
	int		len;
	int		quote;

    s = set_start(s, &quote);
	len = 0;
	while (s[len] && !is_sep(s[len]) && !is_space(s[len]) && s[len] != '"' && s[len] != '\'' && s[len] != '/')
		len++;
	ret = ft_substr(s, 0, len);
	if ((ft_strcmp(ret, "?") == 0))
        return (get_ret_value(ret, s, quote, len));
	while (env && (ft_strcmp(ret, env->name) != 0))
		env = env->next;
	if (env != NULL)
	{
		tmp = ret;
		ret = ft_strjoin(env->content, &s[len]);
		free(tmp);
		if (quote == 1)
		{
			tmp = ret;
			ret = ft_strjoin("\"", tmp);
			free (tmp);
		}
	}
	else
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

char    *insert_env_var(char *str, int i, int quote, t_env_lst *env)
{
    char    *copy;
    char    *var;

	if (str[i] == '"')
    {
        quote = get_to_next_quote(str, i);
        if (str[quote])
            i++;
    }
    var = get_arg(&str[i], env);
    if (var != NULL)
    {
        copy = str;
        str = ft_substr(str, 0, i);
        free(copy);
        copy = str;
        str = ft_strjoin(str, var);
        free(copy);
        free(var);
    }
    return (str);
}

char    *find_env_var(char *str, t_env_lst *env)
{
    int i;
    int quote;

    i = -1;
    quote = 0;
    while (str[++i])
	{
		if (str[i] == '"')
			quote = get_to_next_quote(str, i);
        if (str[i] == '\'')
		{
            i = get_to_next_quote(str, i);
            continue ;
        }	
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && is_sep(str[i]))
			break ;
		if ((str[i] == '"' && str[i + 1] == '$') || str[i] == '$')
		{
            str = insert_env_var(str, i, quote, env);
		}
	}
    return (str);
}
