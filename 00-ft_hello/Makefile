NAME    = hello
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

SRC     = src/ft_putchar.c \
          src/ft_putstr.c \
          src/ft_putnbr.c \
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
