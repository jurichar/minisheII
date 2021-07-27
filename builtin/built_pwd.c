#include "../includes/minishell.h"

int builtin_pwd(t_cmd_lst *lst, t_env_lst *envlst)
{
	char *str;

	str = malloc (1000);
	printf ("%s\n" , getcwd(str, 1000));
	return 0;
}