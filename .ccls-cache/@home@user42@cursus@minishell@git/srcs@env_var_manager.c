/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:19:26 by lebourre          #+#    #+#             */
/*   Updated: 2021/11/02 17:32:17 by jurichar         ###   ########.fr       */
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
		&& valid_identifier(s[len], 2)
		&& s[len] != '"' && s[len] != '\'' && s[len] != '/')
		len++;
	if (quote && s[len] == '"')
		len--;
	if (len == 0 && s[0] == '?')
		return (get_ret_value(ft_strdup("?"), s, quote, 1));
	ret = ft_substr(s, 0, len);
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

char	*get_rest(char *str, char *copy, int i)
{
	int	j;

	j = i;
	while (copy[++i] && copy[i] != ' ' && copy[i] != '"' && copy[i] != '\''
		&& copy[i] != '$' && copy[i] != '=')
		;
	while (copy[i])
	{
		str = ft_realloc(str, ft_strlen(str) + 1);
		str[j++] = copy[i++];
	}
	if (str[0] == '\0')
	{
		free(str);
		str = NULL;
	}
	return (str);
}

char	*insert_env_var(char *str, int i, t_env_lst *env, int squote)
{
	char	*copy;
	char	*var;

	var = get_arg(&str[i], env);
	if (var != NULL)
		return (str = insert_env_var2(str, var, i));
	copy = str;
	str = ft_substr(str, 0, i);
	if (squote)
		str = join_squote(str);
	str = get_rest(str, copy, i);
	free(copy);
	return (str);
}
