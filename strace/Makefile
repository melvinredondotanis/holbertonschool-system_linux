CC = gcc
CFLAGS = -Wall -Werror -g
OBJ = strace_0.o
TARGET = strace

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^

strace_0: strace_0.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJ) $(TARGET)
