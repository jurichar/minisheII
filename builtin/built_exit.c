#include "../includes/minishell.h"

int builtin_exit(t_cmd_lst *lst)
{
	printf("exit code = %d\n", g_exit_code);
	exit(g_exit_code);
	return (0);
}
