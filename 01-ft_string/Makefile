NAME    = string
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

SRC     = src/ft_strlen.c \
          src/ft_putstr_fd.c \
          src/ft_strcpy.c \
          src/ft_strncpy.c \
          src/ft_strcmp.c \
          src/ft_strchr.c \
          tests/main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
