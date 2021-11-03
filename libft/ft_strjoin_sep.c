#include "libft.h"

char	*ft_strjoin_sep(char const *s1, char const *s2, char sep)
{
	char		*new;
	size_t		len;
	size_t		i;
	size_t		j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	new[i++] = sep;
	j = -1;
	while (s2[++j])
		new[i++] = s2[j];
	new[i] = '\0';
	return (new);
}
