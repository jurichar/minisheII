/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lebourre <lebourre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 15:04:01 by lebourre          #+#    #+#             */
/*   Updated: 2021/06/24 23:44:45 by lebourre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t data_ammount, size_t size);
char			*ft_realloc(char *str, int buffer_size);
char			**ft_realloc_double(char **str);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dest, const void *src, int c, size_t n);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
int				ft_atoi(const char *s);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
size_t			ft_strlcat(char *dst, char const *src, size_t size);
size_t			ft_strlcpy(char *dst, char const *src, size_t size);
size_t			ft_strlen(char const *s);
size_t			ft_whereis(const char *s, char *charset);
char			*ft_strncpy(char *dest, const char *src, int n);
char			*ft_strdup(const char *s);
char			*ft_strchr(char const *s, int c);
char			*ft_strrchr(char const *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_strnstr(char const *s1, char const *s2, size_t len);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(char const *s1, char const *s2, size_t n);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
int				ft_toupper(int c);
int				ft_tolower(int c);
char			*ft_s_tolower(char *s);
t_list			*ft_lstnew(void *content);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*d)(void *));
int				ft_lstsize(t_list *lst);
void			ft_lstadd_front(t_list **alst, t_list *new_list);
void			ft_lstadd_back(t_list **alst, t_list *new_list);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));

#endif
