SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LIBFLAGS = -lm

.PHONY: all clean format

all: mathlib-test

mathlib-test: $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f mathlib-test $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]

