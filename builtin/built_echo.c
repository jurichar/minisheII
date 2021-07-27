#include "../includes/minishell.h"

int		is_n(char *s)
{
	int i;

	i = 0;
	if (s[i] == '-')
		i++;
	else
		return (0);
	while (s[i] == 'n')
		i++;
	if (s[i] == '\0')
		return (1);
	return (0);
}

int		builtin_echo(t_cmd_lst *lst, t_env_lst *env, int fd)
{
	int	i;
	int	option;

	option = 0;
	i = 0;
	while (lst->args[i] && (is_n(lst->args[i])) == 1)
		i++;
	if (i > 0)
		option = 1;
	while (lst->args[i])
	{
		if (lst->args[i + 1])
		{
			ft_putstr_fd(lst->args[i], fd);
			ft_putchar_fd(' ', fd);
		}
		else
			ft_putstr_fd(lst->args[i], fd);
		i++;
	}
	if (option == 0)
		printf("\n");
	return (0);
}
