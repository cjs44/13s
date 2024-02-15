SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra `pkg-config --cflags gmp`
LFLAGS = -lm `pkg-config --libs gmp`

.PHONY: all clean cleankeys format

all: keygen encrypt decrypt

keygen: keygen.o randstate.o numtheory.o ss.o
	$(CC) -o $@ $^ $(LFLAGS)

encrypt: encrypt.o randstate.o numtheory.o ss.o
	$(CC) -o $@ $^ $(LFLAGS)

decrypt: decrypt.o randstate.o numtheory.o ss.o
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f keygen encrypt decrypt $(OBJECTS)

cleankeys:
	rm -f *.{pub,priv}

format:
	clang-format -i -style=file *.[ch]
