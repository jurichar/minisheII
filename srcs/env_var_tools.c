/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:48:42 by lebourre          #+#    #+#             */
/*   Updated: 2021/09/23 17:48:57 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
    var = get_arg(&str[i], env, 0);
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
		if (str[i] == '\'' || str[i] == '"')
			quote = get_to_next_quote(str, i);
		if (quote && i == quote)
			quote = 0;
		if (quote == 0 && is_sep(str[i]))
			break ;
		if ((str[i] == '"' && str[i + 1] == '$') || str[i] == '$')
		{
            get_env_var(s, i, quote, env);
		}
	}
    return (str);
}
