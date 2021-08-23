/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/20 17:27:12 by lebourre          #+#    #+#             */
/*   Updated: 2021/08/20 17:27:14 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ft_strstr(char *str, char *to_find, int q)
{
	int i;
	int j;
    int quote;

	i = 0;
	while (str[i])
	{
		j = 0;
        quote = q;
		while (to_find[j] == str[i + j])
		{
            if (to_find[j] == '"' && quote == 1)
                quote = 0;
            else if (to_find[j] == '"' && quote == 0)
                quote = 1;
			if (to_find[j + 1] == '\0' || (to_find[j + 1] == '*' && quote == 0))
				return (&str[i + 1]);
			j++;
		}
		i++;
	}
	return (NULL);
}

char    **get_files(void)
{
    DIR             *d;
    struct dirent   *dir;
    char            **files;
    int             i;
        
    d = opendir(".");
    files = NULL;
    i = 0;
    if (d)
    {
        files = ft_realloc_double(files);
        while ((dir = readdir(d)) != NULL)
        {
            files[i++] = ft_strdup(dir->d_name);
            files = ft_realloc_double(files);
        }
        closedir(d);
    }
    return(files);
}

char    **get_match(char *wd)
{
    char    **files;
    char    **ret_files;
    int     i;
    int     j;
    int     k;
    int     quote;
    int     match;
    char    *file;

    files = get_files();
    i = -1;
    ret_files = ft_realloc_double(NULL);
    k = 0;
    printf("coucou\n");
    while (files[++i])
    {
        j = 0;
        match = 1;
        quote = 0;
        file = files[i];
        while (wd[j] && match == 1)
        {
            if (j == 0 && j != '*' && wd[j] != file[0])
                break ;
            if (quote == 0 && wd[j] == '"')
                quote = 1;
            if (quote == 1 && wd[j] == '"')
                quote = 0;
            if (wd[j] != '*' || (wd[j] == '*' && quote == 1))
            {
                printf("wd[%d] = %c\n", j, wd[j]);
                file = ft_strstr(file, &wd[j], quote);
                printf("file == %s\n", file);
                if (!file)
                {
                    match = 0;
                    break ;
                }
                while (wd[j + 1] && (wd[j + 1] != '*' && quote == 1))
                {
                    if (wd[j] == '"' && quote == 1)
                        quote = 0;
                    else if (wd[j] == '"' && quote == 0)
                        quote = 1;
                    j++;
                }   
            }
            j++;
            if (wd[j] == '\0')
            {
                ret_files[k++] = ft_strdup(files[i]);
                ret_files = ft_realloc_double(ret_files);
            }
        }
    }
    i = -1;
    while (files[++i])
        free(files[i]);
    free(files);
    return (ret_files);
}

char    *wildcard(char *to_find)
{
    char    **tab;
    char    *res;
    char    *tmp;
    int     i;

    tab = get_match(to_find);
    if (tab[0])
        res = ft_strdup(tab[0]);
    else
    {
        free(tab);
        return (NULL);
    }
    i = 0;
    while (tab[++i])
    {
        tmp = res;
        res = ft_strjoin(res, " ");
        free(tmp);
        tmp = res;
        res = ft_strjoin(res, tab[i]);
        free(tmp);
    }
    return (res);
}

// char    *find_wildcard(char *s)
// {
//     int i;

//     i = -1;
//     while (s[++i])
//     {
//         if (s[i] == '"')
//             i = get_to_next_quote(&str[i]);
//         if (s[i] == '*' && (i != 0 && s[i - 1] != '\\'))
//         {
        
//         }
//     }
// }

int main()
{
    printf("%s\n", wildcard("\"ft*\"*.c"));
}