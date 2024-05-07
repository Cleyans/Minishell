NAME := minishell

CC := cc
CFLAGS = -g

FT			= include/libft
LIBFT		= $(FT)/libft.a

SOURCE := 	src/main.c \
			src/list/lst.c \
			src/executing/main_exec.c src/executing/pipe_func.c src/executing/redir_func.c\

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
