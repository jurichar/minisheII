/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:19:26 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/19 14:39:12 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*dup_var_from_list(t_env_lst *env, char *s, int len, int quote)
{
	char	*tmp;
	char	*ret;

	ret = ft_strjoin(env->content, &s[len]);
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
	int		len;
	int		quote;

	s = set_start(s, &quote);
	len = 0;
	while (s[len] && !is_sep(s[len]) && !is_space(s[len])
		&& s[len] != '"' && s[len] != '\'' && s[len] != '/')
		len++;
	if (quote && s[len] == '"')
		len--;
	ret = ft_substr(s, 0, len);
	if ((ft_strcmp(ret, "?") == 0))
		return (get_ret_value(ret, s, quote, len));
	while (env && (ft_strcmp(ret, env->name) != 0))
		env = env->next;
	free(ret);
	if (env == NULL)
		return (NULL);
	ret = dup_var_from_list(env, s, len, quote);
	return (ret);
}

char	*insert_env_var2(char *str, char *var, int i)
{
	char	*copy;

	copy = str;
	str = ft_substr(str, 0, i);
	free(copy);
	copy = str;
	str = ft_strjoin(str, var);
	free(copy);
	free(var);
	return (str);
}

char	*insert_env_var(char *str, int i, t_env_lst *env)
{
	char	*copy;
	char	*var;

	var = get_arg(&str[i], env);
	if (var != NULL)
		str = insert_env_var2(str, var, i);
	else
	{
		copy = str;
		str = ft_substr(str, 0, i);
		free(copy);
	}
	return (str);
}

char	*find_env_var(char *str, t_env_lst *env)
{
	int		i;
	int		quote;
	char	*s;

	s = ft_strdup(str);
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
		if (str[i] == '$')
			s = insert_env_var(s, i, env);
	}
	free(str);
	return (s);
}
