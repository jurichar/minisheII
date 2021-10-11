#include "../includes/minishell.h"

int	get_env_size(t_env_lst *lst)
{
	int		size;

	size = 0;
	while (lst)
	{
		if (lst->equal == 1)
			size++;
		lst = lst->next;
	}
	return (size);
}

char	**update_envp(t_env_lst *lst, int size_env)
{
	char	**new;
	char	*buffer;
	int		i;

	new = malloc(sizeof(char *) * (size_env + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (lst)
	{
		if (lst->equal)
		{
			new[i] = ft_strjoin(lst->name, "=");
			if (lst->content)
			{
				buffer = new[i];
				new[i] = ft_strjoin(new[i], lst->content);
				free(buffer);
			}
			i++;
		}
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}