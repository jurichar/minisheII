NAME = minishell

RED="\033[1;31m"
GRN="\033[1;32m"
YLW="\033[1;33m"
END="\033[0m"

CC = gcc

INCLUDES = -I libft/

CFLAGS = -Wall -Wextra -Werror -Wuninitialized -g3 $(INCLUDES)
# CFLAGS = $(INCLUDES)

DEBUG = -fsanitize=address -fno-omit-frame-pointer

LDFLAGS = libft/libft.a

SRC = 	$(addprefix srcs/, $(shell ls srcs/ | egrep "[.]"c)) \
		$(addprefix builtin/, $(shell ls builtin/ | egrep "[.]"c)) \
		$(addprefix exec/, $(shell ls exec/ | egrep "[.]"c))

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): lib
	@printf $(YLW)"[Minishell compilation...]%-30s\r"
	$(CC) $(CFLAGS) $(SRC) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib $(LDFLAGS) -I ~/.brew/opt/readline/include
	@printf $(GRN)"[Minishell ready !!]%-30s\r"
	@printf $(END)

readline:
	@sudo apt-get install libreadline-dev

debug: lib
	@printf $(YLW)"[Minishell compilation...]%-30s\r"
	$(CC) $(CFLAGS) $(DEBUG) $(SRC) -o $(NAME) -lreadline -L ~/.brew/opt/readline/lib $(LDFLAGS) -I ~/.brew/opt/readline/include
	@printf $(GRN)"[Minishell ready !!]%-30s\r"
	@printf $(END)

lib:
	@printf $(YLW)"[Libft compilation...]%-30s\r"
	@make -C libft/
	@printf $(GRN)"[Libft ready !!]%-30s\r"
	@printf $(END)

clean:
	@printf $(RED)"[Minishell remove...]%-30s\r"
	@$(RM) $(OBJ)
	@printf $(RED)"[All .o files removed !!]%-30s\r"
	@printf $(END)

fclean: clean
	@printf $(RED)"[Minishell remove...]%-30s\r"
	@$(RM) $(NAME)
	@printf $(RED)"[Minishell removed !!]%-30s\r"
	@printf $(END)

clear: fclean
	@printf $(RED)"[Libft remove...]%-30s\r"
	@make fclean -C libft
	@printf $(RED)"[Minishell remove !!]%-30s\r"
	@$(RM) historic
	@printf $(END)

re: fclean all

.SILENT:

.PHONY: all clear clean fclean lib readline
