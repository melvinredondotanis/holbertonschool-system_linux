CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c89
NAME = hnm
SOURCES = hnm.c displays_symbols.c swaps.c sections.c symbols.c

$(NAME): $(SOURCES) hnm.h
	$(CC) $(CFLAGS) -o $(NAME) $(SOURCES)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
