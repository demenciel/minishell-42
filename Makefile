
NAME	= minishell
CFLAGS	= -g -Wextra -Wall -Werror #-fsanitize=address
#
SRC_PATH = src/

OBJ_PATH = obj/

READ_PATH	= libs/readline
RLINE		= $(READ_PATH)/libreadline.a
LIBRLINE	= readline-8.2

LIBFT_DIR = inc/libft/
LIBFT	= 	$(LIBFT_DIR)/libft.a
HEADERS	= -I ./include


SRC		=  main.c \
			exec/pipex.c \
			exec/redirect.c \
			exec/error_utils.c \
			exec/builtin.c \
			exec/exec_builtins.c \
			exec/export.c \
			exec/export2.c \
			exec/exit.c \
			parsing/parsing.c \
			parsing/utils.c \
			parsing/link_list.c \
			parsing/pars.c \
			parsing/check.c \
			parsing/com_list.c \
			parsing/utils_com.c \

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:%.c=%.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

GREEN = \033[0;92m
RED = \033[0;91m
RESET = \033[0m

all: readline $(NAME)
	@exec 2>/dev/null

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

readline:
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
	@printf "$(GREEN)minishell and libft compiling: done$(RESET)\n"

 $(LIBFT):
	@make -C $(LIBFT_DIR)

debug: $(NAME)
	@$(CC) -g $(OBJS) $(HEADERS) $(LIBFT) -o $(NAME)

clean:
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_PATH)
	@printf "$(RED)minishell and libft clean: done$(RESET)\n"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
#	@rm -rf $(READ_PATH)
	@rm -f $(NAME)

re: fclean all

# Debug leaks
leak: all
	@leaks --atExit --list -- ./minishell

leaks: all
	@valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=supp.txt ./minishell

.PHONY: all, clean, fclean, re, leak, leaks
