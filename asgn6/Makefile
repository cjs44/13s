SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra
LFLAGS = -lm

.PHONY: all clean format

all: encode decode

encode: encode.o trie.o word.o io.o
	$(CC) -o $@ $^ $(LFLAGS)

decode: decode.o trie.o word.o io.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f encode decode $(OBJECTS)

format:
	clang-format -i -style=file *.[ch]
