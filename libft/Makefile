SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memccpy.c \
		ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
		ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c   \
		ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c  \
		ft_realloc.c ft_realloc_double.c ft_strcmp.c ft_s_tolower.c \
		ft_strncpy.c		\
		ft_lstnew.c 		\
		ft_lstadd_front.c 	\
		ft_lstadd_back.c 	\
		ft_lstclear.c 		\
		ft_lstdelone.c 		\
		ft_lstiter.c		\
		ft_lstlast.c		\
		ft_lstmap.c			\
		ft_lstsize.c

OBJ = $(SRC:.c=.o)

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) 
	@ar rcs $(NAME) $(OBJ)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean bonus
