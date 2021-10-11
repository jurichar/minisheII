#include "libft.h"

char	**ft_strdoubledup(char **tab)
{
	char	**res;
	int		size;
	int		i;

	size = ft_strdoublelen(tab);
	res = malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (tab[++i])
		res[i] = ft_strdup(tab[i]);
	res[i] = NULL;
	return (res);
}