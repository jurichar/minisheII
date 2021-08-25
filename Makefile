# NAME = minishell

# RED="\033[1;31m"
# GRN="\033[1;32m"
# YLW="\033[1;33m"
# END="\033[0m"

# SRC_DIR = ./srcs/
# SRC_NAMES = $(shell ls $(SRC_DIR) | grep -E ".+\.c")
# SRC = $(addprefix $(SRC_DIR), $(SRC_NAMES))

# DIR_INCLUDES = ./includes/

# BUILTIN_DIR = ./builtin/
# BUILTIN_NAMES = $(shell ls $(BUILTIN_DIR) | grep -E ".+\.c")
# BUILTIN = $(addprefix $(BUILTIN_DIR), $(BUILTIN_NAMES))

# LIBDIR = ./libft/
# LIBFT = ./libft/libft.a

# CC = gcc
# CLFLAGS =# -g3 -Wall -Wextra -Werror
# BUG = 	-Wsometimes-uninitialized -Uninitialized \
# 		--analyze -std=c11 -pedantic

# RM = rm -f

# BUILDDIR = ./build/

# BUILDOBJS = $(addprefix $(BUILDDIR), $(SRC_NAMES:.c=.o), $(BUILTIN_NAMES:.c=.o))


# all: $(BUILDDIR) $(LIBFT) $(NAME)

# $(BUILDDIR):
# 	mkdir -p $(BUILDDIR)

# $(BUILDDIR)%.o:$(SRCDIR)%.c
# 	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<


# $(NAME): $(BUILDOBJS)
# 	$(CC) \
# 	$(CFLAGS) -o \
# 	$(NAME) $(BUILDOBJS) $(LIBFT)


# sani: lib $(OBJ)
# 	@printf $(YLW)"[Minishell compilation...]%-30s\r"
# 	@$(CC) $(OBJ) -g3 -O0 -fsanitize=address $(FLIB) $(NAME) -lreadline
# 	@printf $(GRN)"[Minishell ready !]%-30s\n"
# 	@printf $(END)


# $(LIBFT):
# 	make -C $(LIBDIR)

# clean:
# 	rm -rf $(BUILDDIR)
# 	make -C $(LIBDIR) clean

# fclean: clean
# 	@$(RM) $(NAME)
# 	@$(RM) a

# cleanlib:
# 	@printf $(RED)"[Libft remove...]%-30s\r"
# 	@printf $(END)
# 	@make fclean -C libft

# clear:	fclean cleanlib
# 	@$(RM) historic

# re: fclean all

# .PHONY : all fclean clear re
# .SILENT:

# Project file
NAME = minishell

# Project builds and dirs
SRCDIR = ./srcs/
BUILDIR = ./builtin/
SRCNAMES = $(shell ls $(SRCDIR) | grep -E ".+\.c")
BUILNAMES = $(shell ls $(BUILDIR) | grep -E ".+\.c")
SRC = $(addprefix $(SRCDIR), $(SRCNAMES))
BUIL = $(addprefix $(BUILDIR), $(BUILNAMES))
INC = ./includes/
BUILDDIR = ./build/
BUILDOBJS = $(addprefix $(BUILDDIR), $(SRCNAMES:.c=.o))

# Libft builds and dirs
LIBDIR = ./libft/
LIBFT = ./libft/libft.a
LIBINC = ./libft/includes/

# Optimization and Compiler flags and commands
CC = gcc
CFLAGS = -Wall -Werror -Wextra

# Debugging flags
DEBUG = -g

# Main rule
all: $(BUILDDIR) $(LIBFT) $(NAME)

# Object dir rule
$(BUILDDIR):
	mkdir -p $(BUILDDIR)

# Objects rule
$(BUILDDIR)%.o:$(SRCDIR)%.c
	$(CC) $(CFLAGS) -I$(LIBINC) -I$(INC) -o $@ -c $<

# Project file rule
$(NAME): $(BUILDOBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(BUILDOBJS) $(LIBFT)

# Libft rule
$(LIBFT):
	make -C $(LIBDIR)

# Cleaning up the build files
clean:
	rm -rf $(BUILDDIR)
	make -C $(LIBDIR) clean

# Getting rid of the project file
fclean: clean
	rm -rf $(NAME)
	make -C $(LIBDIR) fclean

# Do both of the above
re: fclean all

# Just in case those files exist in the root dir
.PHONY: all fclean clean re