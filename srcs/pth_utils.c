/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pth_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 17:28:20 by lebourre          #+#    #+#             */
/*   Updated: 2021/10/21 17:41:58 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	init_pth_var_check_s(t_pth_var *var, char *s, int i)
{
	var->qt = 0;
	var->sts = 0;
	if (!s || !*s || !s[i])
		return (1);
	return (0);
}
