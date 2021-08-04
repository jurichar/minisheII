#include "../includes/minishell.h"

int builtin_env(t_cmd_lst *lst, t_env_lst *envlst)
{
	while (envlst)
	{
		printf("%s=%s\n", envlst->name, envlst->content);
		envlst = envlst->next;
	}
	return (0);
}
