# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acouture <acouture@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 16:55:29 by acouture          #+#    #+#              #
#    Updated: 2023/05/24 16:56:31 by acouture         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell
CFLAGS	:= -g -Wextra -Wall -Werror

SRC_PATH = src/
OBJ_PATH = obj/

HEADERS	:= -I ./include
SRC		:= main.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

all: makelibft $(NAME)
	@exec 2>/dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) -o $(NAME)
	@printf "$(GREEN)minishell compiling: done$(RESET)\n"

debug: $(NAME)
	@$(CC) -g $(OBJS) $(HEADERS) -o $(NAME)

clean:
	@$(MAKE) clean -C 
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)minishell clean: done$(RESET)\n"

fclean: clean
	@$(MAKE) fclean -C 
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
