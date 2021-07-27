#include "../includes/minishell.h"

int builtin_unset(t_cmd_lst *lst, t_env_lst *env)
{
	int	i;

	i = -1;
	while (lst->args[++i])
		ft_env_remove_if(&env, lst->args[i], &ft_strcmp);
	return 0;
}
