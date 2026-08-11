NAME    = memory
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

SRC     = src/ft_strlen.c \
          src/ft_memset.c \
          src/ft_bzero.c \
          src/ft_memcpy.c \
          src/ft_strdup.c \
          src/ft_calloc.c \
          src/ft_free_tab.c \
          tests/main.c

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

# Compila con AddressSanitizer para detectar fugas y errores de memoria.
# Sin -Werror: un aviso no debe impedir ejecutar el sanitizer.
debug: $(SRC)
	$(CC) -Wall -Wextra -g -fsanitize=address $(SRC) -o debug

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) debug

re: fclean all

.PHONY: all debug clean fclean re
