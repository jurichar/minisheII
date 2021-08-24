NAME = minishell

RED="\033[1;31m"
GRN="\033[1;32m"
YLW="\033[1;33m"
END="\033[0m"

DIR_BUILTIN = builtin/
DIR_SRCS = srcs/

CC = clang -g3 -Wall -Wextra -Werror -Wsometimes-uninitialized -Uninitialized # --analyze # -std=c11 -pedantic

FLIB = -g3 -I libft/ -lft -L libft/ -g3 -o

SRC_BUILTIN =	built_cd.c \
				built_echo.c \
				built_export.c \
				built_export_sort.c \
				built_env.c \
				built_pwd.c \
				built_exec.c \
				built_exit.c \
				built_unset.c \
				ft_execve.c \
				ft_pipe.c \
				built_utils.c \
				ft_redir.c

SRC_SRCS =	main.c \
		ft_split_args.c \
		list_tools.c \
		ft_is.c \
		ft_split_cmd.c \
		get_next_line.c \
		utils.c \
		ft_lstnew_env.c \
		set_canonic.c \
		manage_input.c \
		historic.c \
		parse_redir.c \
		skip.c \
		cmd_utils.c 

SRC = 	$(addprefix $(DIR_SRCS), $(SRC_SRCS)) \
		$(addprefix $(DIR_BUILTIN), $(SRC_BUILTIN))

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)


$(NAME): lib $(OBJ) 
	@printf $(YLW)"[Minishell compilation...]%-30s\r"
	@$(CC) $(OBJ) $(FLIB) $(NAME) -lreadline
	@printf $(GRN)"[Minishell ready !!]%-30s\n"
	@printf $(END)

sani: lib $(OBJ)
	@printf $(YLW)"[Minishell compilation...]%-30s\r"
	@$(CC) $(OBJ) -g3 -O0 -fsanitize=address $(FLIB) $(NAME) -lreadline
	@printf $(GRN)"[Minishell ready !]%-30s\n"
	@printf $(END)


lib:
	@printf $(YLW)"[Libft compilation...]%-30s\r"
	@make -C libft/
	@printf $(GRN)"[Libft done !]%-30s\r"
	@printf $(END)

clean:
	@printf $(RED)"[Minishell remove...]%-30s\r"
	@printf $(END)
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) a

cleanlib:
	@printf $(RED)"[Libft remove...]%-30s\r"
	@printf $(END)
	@make fclean -C libft

clear: fclean cleanlib
	@$(RM) historic

re: fclean all

go : re
	@printf $(GRN)"[Launch Minishell...]\n"
	@printf $(END)
	@./minishell
.SILENT:
