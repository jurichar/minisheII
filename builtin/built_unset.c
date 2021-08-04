#include "../includes/minishell.h"

int builtin_unset(t_cmd_lst *lst, t_env_lst *env)
{
	int	i;
	int	j;

	i = -1;
	while (lst->args[++i])
	{
		j = -1;
		while (lst->args[i][++j])
		{
			if (!ft_isalnum(lst->args[i][j]))
			{
				printf("unset:\t`%s': not a valid indentifier\n", lst->args[0]);
				return (1);
			}
		}
		ft_env_remove_if(&env, lst->args[i], &ft_strcmp);
	}
	return (0);
}
