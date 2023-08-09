# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rofontai <rofontai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/09 07:40:10 by acouture          #+#    #+#              #
#    Updated: 2023/08/09 10:38:36 by rofontai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CFLAGS	:= -g -Wextra -Wall -Werror -fsanitize=address
#
SRC_PATH = src/

OBJ_PATH = obj/

LIBFT_DIR	= ./inc/libft
LIBFT	= $(LIBFT_DIR)/libft.a

READ_PATH	= libs/readline
RLINE		= $(READ_PATH)/libreadline.a
LIBRLINE	= readline-8.2

# LIBFT_A = 	libft.a
# LIBF_DIR = 	inc/libft/
# LIBFT  = 	$(addprefix $(LIBF_DIR), $(LIBFT_A))
# HEADERS	:= -I ./include


SRC		:=  main.c \
			exec/executables/main_exec.c \
			exec/executables/pipex.c \
			exec/executables/redirect.c \
			exec/executables/error_utils.c \
			exec/builtins/env.c \
			exec/builtins/builtin.c \
			exec/builtins/exec_builtins.c \
			exec/builtins/echo.c \
			exec/builtins/cd.c \
			exec/builtins/unset.c \
			exec/export/export.c \
			exec/export/export2.c \
			exec/export/export3.c \
			parsing/checking.c \
			parsing/com_list.c \
			parsing/com_utils.c \
			parsing/free.c \
			parsing/init.c \
			parsing/parsing.c \
			parsing/utils.c \
			parsing/a_supp.c \
			parsing/exit.c \
			parsing/signal.c \


SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

all: readline $(NAME) #makelibft
	@exec 2>/dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# makelibft:
# 	@$(MAKE) -C $(LIBF_DIR)

readline	:
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
    	curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz; \
		mkdir -p $(READ_PATH); \
    	tar -xf $(LIBRLINE).tar.gz; \
        rm -rf $(LIBRLINE).tar.gz; \
        cd $(LIBRLINE) && bash configure && make; \
        mv ./libreadline.a ../libs/readline; \
        rm -rf ../$(LIBRLINE); \
        echo "\n----- $(GREEN)Readline $(RESET) succesfully configured ✅ -----\n"; \
    fi

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RLINE) -lncurses $(HEADERS) -o $(NAME)
	@printf "$(GREEN)minishell compiling: done$(RESET)\n"

 $(LIBFT)	:
	@make -C $(LIBFT_DIR)

debug: $(NAME)
	@$(CC) -g $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)minishell clean: done$(RESET)\n"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
#	@rm -rf $(READ_PATH)
	@rm -f $(NAME)

re: fclean all

# Debug leaks
leak : all
	@leaks --atExit --list -- ./minishell

leaks : all
	@valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --suppressions=supp.txt ./minishell

.PHONY: all, clean, fclean, re, leak, leaks
