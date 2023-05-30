# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouture <acouture@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/29 13:48:07 by rofontai          #+#    #+#              #
#    Updated: 2023/05/30 12:52:55 by acouture         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CFLAGS	:= -g -Wextra -Wall -Werror
#
SRC_PATH = src/

OBJ_PATH = obj/

READ_PATH	= libs/readline
RLINE		= $(READ_PATH)/libreadline.a
LIBRLINE	= readline-8.2

LIBFT_A = 	libft.a
LIBF_DIR = 	inc/libft/
LIBFT  = 	$(addprefix $(LIBF_DIR), $(LIBFT_A))

HEADERS	:= -I ./include -I $(LIBMLX)/include 
SRC		:=  main.c \
			pipex/pipex.c \
			pipex/pipex_utils.c \
			utils/errors.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

all: makelibft readline $(NAME)
	@exec 2>/dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

makelibft:
	@$(MAKE) -C $(LIBF_DIR)

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

$(NAME): $(OBJS)

	@$(CC) $(CFLAGS) $(OBJS) $(RLINE) $(LIBFT) -lncurses $(HEADERS) -o $(NAME)
	@printf "$(GREEN)minishell compiling: done$(RESET)\n"

debug: $(NAME)
	@$(CC) -g $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)

clean:
#	@$(MAKE) clean -C
	@$(MAKE) clean -C $(LIBF_DIR)
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)minishell clean: done$(RESET)\n"

fclean: clean
#	@$(MAKE) fclean -C
	@$(MAKE) fclean -C $(LIBF_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
