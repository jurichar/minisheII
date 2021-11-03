#include "../includes/minishell.h"

char	*find_env_var(char *str, t_env_lst *env, int i, int quote)
{
	char	*s;

	s = ft_strdup(str);
	while (s[++i])
	{
		quote = double_quote_status(quote, i, s);
		if (quote == 0 && s[i] == '\'')
		{
			quote = get_to_next_quote(s, i);
			if (s[quote])
				i = quote;
			continue ;
		}
		if (quote == 0 && is_sep(s[i]))
			break ;
		else if (s[i] == '$')
		{
			s = insert_env_var(s, i, env, 0);
			if (!s)
				return (NULL);
			i = -1;
		}
	}
	free(str);
	return (s);
}
