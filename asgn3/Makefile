SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra -gdwarf-4
LIBFLAGS = -lm

.PHONY: all clean format

all: sorting

sorting: $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f sorting $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]
