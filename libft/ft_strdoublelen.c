#include "libft.h"

size_t	ft_strdoublelen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}