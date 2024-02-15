SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra `pkg-config --cflags ncurses`
LFLAGS = -lm `pkg-config --libs ncurses`

.PHONY: all clean format

all: life

life: $(OBJECTS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f life $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]

