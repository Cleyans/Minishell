NAME := minishell

CC := cc
CFLAGS = -Wall -Wextra -Werror -g
FT			= include/libft
LIBFT		= $(FT)/libft.a

SOURCE := 	src/main.c src/init.c src/free.c src/testing.c src/error.c\
			src/list/lst.c \
			src/executing/main_exec.c src/executing/pipe_func.c src/executing/utils_exec.c src/executing/redir.c\
			src/signals/signals.c \
			src/builtins/builtins_func.c src/builtins/echo.c src/builtins/builtins_utils.c src/builtins/parent_child_call.c src/builtins/env.c src/builtins/export.c src/builtins/unset.c\
			src/parssing/parss.c src/parssing/heredoc_redir.c src/parssing/args.c src/parssing/quotes.c src/parssing/verif_white_space.c\

OBJ 	= $(SOURCE:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

$(LIBFT): $(FT)
	$(MAKE) -C $(FT)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY:		all bonus clear clean fclean re
