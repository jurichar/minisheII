#include <libc.h>

void init(char **str)
{
    str[0] = strdup("coucou");
    str[1] = strdup("o revoir");
    str[2] = 0;
}

void ft_free(char **str)
{
    // free(str[0]);
    // free(str[1]);
    // free(str);
}

int main ()
{
    char **str;
    str = malloc(sizeof(char *) * 3);
    init(str);
    printf ("str[0]= %s\n", str[0]);
    printf ("str[1]= %s\n", str[1]);
    ft_free(str);
}