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

char *ft_strstr(char *str, char *to_find)
{
	int i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (to_find[j] == str[i + j])
		{
			if (to_find[j + 1] == '\0' || to_find[j + 1] == '*')
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

char    **wildcard(char *wd)
{
    char    **files;
    char    **ret_files;
    int     i;
    int     j;
    int     k;
    int     match;
    char    *file;

    files = get_files();
    i = -1;
    ret_files = ft_realloc_double(NULL);
    i = -1;
    k = 0;
    while (files[++i])
    {
        j = 0;
        match = 1;
        file = files[i];
        while (wd[j] && match == 1)
        {
            if (j == 0 && j != '*' && wd[j] != file[0])
                break ;
            if (wd[j] != '*')
            {
                file = ft_strstr(file, &wd[j]);
                if (!file)
                {
                    match = 0;
                    break ;
                }
                while (wd[j + 1] && wd[j + 1] != '*')
                    j++;
            }
            j++;
            if (wd[j] == '\0')
            {
                ret_files[k++] = ft_strdup(files[i]);
                ret_files = ft_realloc_double(ret_files);
            }
        }
    }
    return (ret_files);
}

int     main()
{
    char    **res = wildcard("ft*\0");
    int     i = -1;

    while (res[++i])
        printf("match: %s\n", res[i]);
}