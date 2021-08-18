/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jurichar <jurichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 17:36:08 by jurichar          #+#    #+#             */
/*   Updated: 2021/08/18 21:37:41 by jurichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_exit( void )
{
	printf("exit code = %d\n", g_exit_code);
	exit(g_exit_code);
	return (g_exit_code);
}
