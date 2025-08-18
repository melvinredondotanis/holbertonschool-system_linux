CC = gcc

CFLAGS = -std=c90 -Wall -Werror -Wextra -pedantic
FILES_0 = strace_0.c
FILES_1 = strace_1.c
FILES_2 = strace_2.c
FILES_3 = strace_3.c
FILES_4 = strace_4.c


LDFLAGS =

all: strace_0 strace_1 strace_2 strace_3 strace_4

strace_0: strace_0.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

strace_1: strace_1.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

strace_2: strace_2.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

strace_3: strace_3.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

strace_4: strace_4.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

clean:
	rm -f strace_0 strace_1 strace_2 strace_3 strace_4

.PHONY: all clean
