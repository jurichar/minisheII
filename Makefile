NAME = minishell

RED="\033[1;31m"
GRN="\033[1;32m"
YLW="\033[1;33m"
END="\033[0m"

CC = gcc

INCLUDES = -I libft/

CFLAGS = -Wall -Wextra -Werror $(INCLUDES) --analyze

LDFLAGS = -L libft/ -lft

SRC = 	$(addprefix srcs/,$(shell ls srcs/ | egrep "[.]"c)) \
		$(addprefix builtin/, $(shell ls builtin/ | egrep "[.]"c))

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): lib $(OBJ)
	@printf $(YLW)"[Minishell compilation...]%-30s\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME) -lreadline
	@printf $(GRN)"[Minishell ready !!]%-30s\n"
	@printf $(END)

lib:
	@printf $(YLW)"[Libft compilation...]%-30s\n"
	@make -C libft/
	@printf $(GRN)"[Libft ready !!]%-30s\n"
	@printf $(END)

clean:
	@printf $(RED)"[Minishell remove...]%-30s\n"
	@$(RM) $(OBJ)
	@printf $(RED)"[All .o files removed !!]%-30s\n"
	@printf $(END)

fclean: clean
	@printf $(RED)"[Minishell remove...]%-30s\n"
	@$(RM) $(NAME)
	@printf $(RED)"[Minishell removed !!]%-30s\n"
	@printf $(END)

clear: fclean
	@printf $(RED)"[Libft remove...]%-30s\n"
	@make fclean -C libft
	@printf $(RED)"[Minishell remove !!]%-30s\n"
	@$(RM) historic
	@printf $(END)

re: fclean all

.SILENT:

# tester: $(OBJ)
# 				$(CC) -o $@ $^ $(LDFLAGS)

# main.o: includes/minishell.h

# %.o:	%.c
# 		$(CC) -o $@ -c $< $(CFLAGS)
# clean:
# 			rm -f */*.o core

# mrproper:	clean
# 			rm -f $(NAME)