NAME= pipex.a

CC = gcc
CFLAGS= -Wall -Werror -Wextra -g
HEADER= pipex.h
RM= rm -rf
NAME = pipex
#DEBUG = -fsanitize=address

LIBFT= include/libft/libft.a

FILES=	include/get_next_line/get_next_line.c \
		funcs/main.c \
		funcs/extra_funcs.c \
		funcs/path.c \
		funcs/error.c \
		funcs/pipex.c \
		funcs/here_doc.c

O_FILES= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(O_FILES)
	$(MAKE) -C include/libft
	$(CC) $(CFLAGS) $(DEBUG) $(O_FILES) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C include/libft
	$(RM) $(O_FILES)
	
fclean: clean
	$(MAKE) fclean -C include/libft
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re