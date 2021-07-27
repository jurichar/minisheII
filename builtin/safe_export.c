/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 13:50:56 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/07 11:32:26 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env_lst        *env_sort(t_env_lst *list, int i)
{
    t_env_lst    *curr;
    t_env_lst    *begin;
    t_env_lst    *swap;
    t_env_lst    *tmp_next;
    t_env_lst    *prev;

    curr = list;
    begin = list;
    prev = list;
	i = 0;
    while (curr->next)
    {
        if ((ft_strcmp(curr->name, curr->next->name)) > 0)
        {
            swap = curr;
            tmp_next = swap->next->next;
            curr = curr->next;
            curr->next = swap;
            curr->next->next = tmp_next;
            if (i == 0)
                begin = curr;
            else
                prev->next = curr;
            curr = begin;
            i = 0;
        }
        else
        {
            prev = curr;
            curr = curr->next;
            i++;
        }
    }
    return (begin);
}

int builtin_export(t_cmd_lst *lst, t_env_lst *envlst)
{
    envlst = env_sort(envlst, 0);
    while (envlst)
    {
        printf("%s=%s\n", envlst->name, envlst->content);
        envlst = envlst->next;
    }
    return 0;ß
}
