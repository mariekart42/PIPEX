NAME= pipex.a

CC = gcc
CFLAGS= -Wall -Werror -Wextra -g
HEADER= pipex.h
RM= rm -rf
NAME = pipex
#DEBUG = -fsanitize=address

FILES=	main.c \
		ft_split.c \
		extra_funcs.c \
		path.c \
		pipex.c \
		error.c

O_FILES= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(O_FILES) $(HEADER)
	$(CC) $(CFLAGS) $(DEBUG) $(O_FILES) -o $(NAME)

clean:
	$(RM) $(O_FILES)
	
fclean: clean
	$(RM) $(NAME)
	
re: fclean all

g:
	@gcc -g -fsanitize=address $(FILES) $(CFLAGS)
# -fsanitize=address
.PHONY: all clean fclean re