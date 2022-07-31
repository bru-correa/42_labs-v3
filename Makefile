ifndef VERBOSE
.SILENT:
endif

RED					= \033[1;31m
YELLOW				= \033[1;33m
GREEN				= \033[1;32m
NOCOLOR				= \033[0m
DONE_MSG			= "$(GREEN)Done!$(NOCOLOR)"
COMPILING_MSG		= "$(YELLOW)Compiling...$(NOCOLOR)"
CLEANING_MSG		= "$(RED)Cleaning up...$(NOCOLOR)"

NAME				= monitoring
CC					= gcc
CFLAGS				= -Wall -Wextra -Werror $(CFLAGS_LIBS) -I$(INCLUDE_DIR)
CFLAGS_LIBS			= $(CFLAGS_LIBFT) $(CFLAGS_LIBCURL)
CFLAGS_LIBCURL		= -lcurl
CFLAGS_LIBFT		= -lft -L $(LIBFT_DIR)

INCLUDE_DIR			= include
SRC_DIR				= src
OBJ_DIR				= obj
LIB_DIR				= lib

LIBFT_DIR			= lib/libft

SRC_FILES			= $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES			= $(patsubst %, $(OBJ_DIR)/%.o, \
						$(basename $(notdir $(SRC_FILES))))
MAIN				= $(NAME).c

all:				$(NAME)

required:			compile_message $(OBJ_DIR) $(OBJ_FILES) libft

libft:
					$(MAKE) -C $(LIBFT_DIR)

$(NAME):			required
					$(CC) -g $(MAIN) $(OBJ_FILES) $(CFLAGS) -o $(NAME)
					echo $(DONE_MSG)

$(OBJ_DIR):
					mkdir -p $@

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					$(CC) -c -g $< $(CFLAGS) -o $@

clean:
					echo $(CLEANING_MSG)
					rm -rf $(OBJ_DIR)

fclean:				clean
					rm -f $(NAME)

re:					fclean all

re_bonus:			fclean bonus

compile_message:
					echo $(COMPILING_MSG)

run:				all
					./monitoring

.PHONY:	all run clean fclean re run libft
