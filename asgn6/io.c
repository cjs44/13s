// io.c

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "io.h"
#include "word.h"
#include "code.h"
#include "endian.h"

uint64_t total_syms = 0; // To count the symbols processed.
uint64_t total_bits = 0; // To count the bits processed.

// read from infile, write to buffer, return bytes read
int read_bytes(int infile, uint8_t *buf, int to_read) {
    // count variable
    int count = 0;
    int r = 1; // start non zero so it enters loop
    // loop calls to read
    while (count < to_read && r > 0) {
        // read from infile to buffer
        r = read(infile, buf, to_read);
        count += r;
    }
    return count;
}

// write to outfile, read from buffer, return bytes written
int write_bytes(int outfile, uint8_t *buf, int to_write) {
    // count variable
    int count = 0;
    int w = 1; // start non zero so it enters loop
    // loop calls to write
    while (count < to_write && w > 0) {
        // write to outfile from buffer
        w = write(outfile, buf, to_write);
        count += w;
    }
    return count;
}

// read  file header from infile to pointer
void read_header(int infile, FileHeader *header) {
    // read in using read funct
    read_bytes(infile, (uint8_t *) header, sizeof(FileHeader));
    // check endianness
    if (big_endian()) {
        //swap magic and protection
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    // verify magic number
    assert(header->magic != MAGIC);
}

// write file header from pointer to outfile
void write_header(int outfile, FileHeader *header) {
    // check endianness
    if (big_endian()) {
        //swap magic and protection
        header->magic = swap32(header->magic);
        header->protection = swap16(header->protection);
    }
    // write to outfile
    write_bytes(outfile, (uint8_t *) header, sizeof(FileHeader));
}

// global buffers and pos trackers
static uint8_t sym_buffer[BLOCK];
static int sym_pos = 0;
static uint8_t pair_buffer[BLOCK];
static int pair_pos = 0;

// read symbol from infile to pointer
bool read_sym(int infile, uint8_t *sym) {
    int r = 0;
    // check is buffer is full
    if (sym_pos == BLOCK) {
        // read more bytes
        r = read_bytes(infile, sym_buffer, BLOCK);
        if (r == 0) {
            return false;
        }
        sym_pos = 0;
    }
    // read single sym from buffer
    *sym = sym_buffer[sym_pos];
    sym_pos += 1;
    total_syms += 1;
    return true;
}

// write code/sym pair to outfile
void write_pair(int outfile, uint16_t code, uint8_t sym, int bitlen) {
    // current bit
    uint8_t bit;
    // write code to buffer
    for (int i = 0; i < bitlen; i++) {
        bit = (code >> i) & 1;
        // byte and bit location
        int byte_loc = pair_pos / 8;
        int bit_loc = pair_pos % 8;
        pair_buffer[byte_loc] = pair_buffer[byte_loc] | (bit << bit_loc);
        pair_pos += 1;
        // if at end, write out
        if (pair_pos == BLOCK * 8) {
            flush_pairs(outfile);
        }
    }
    // write symbol to buffer
    for (int i = 0; i < 8; i++) {
        bit = (sym >> i) & 1;
        // byte and bit location
        int byte_loc = pair_pos / 8;
        int bit_loc = pair_pos % 8;
        pair_buffer[byte_loc] = pair_buffer[byte_loc] | (bit << bit_loc);
        pair_pos += 1;
        // if at end, write out
        if (pair_pos == BLOCK * 8) {
            flush_pairs(outfile);
        }
    }
}

// write any remaining pairs to outfile
void flush_pairs(int outfile) {
    // if the pair_pos hasn't been reset
    if (pair_pos != 0) {
        write_bytes(outfile, pair_buffer, BLOCK);
        total_bits += pair_pos;
        pair_pos = 0;
    }
}

// read pair from infile to pointers
bool read_pair(int infile, uint16_t *code, uint8_t *sym, int bitlen) {
    // current bit
    uint8_t b = 0;
    *code = 0;
    *sym = 0;
    // code into code pointer
    for (int i = 0; i < bitlen; i++) {
        // set bit by bit
        //b = read_bit();
        int byte_loc = pair_pos / 8;
        b = (pair_buffer[byte_loc] >> i) & 1;
        *code = *code | (b << i);
        pair_pos += 1;
        // if buffer is full
        if (pair_pos == BLOCK) {
            read_bytes(infile, pair_buffer, BLOCK);
            memset(pair_buffer, 0, BLOCK);
            pair_pos = 0;
        }
    }
    // symbol into sym pointer
    for (int i = 0; i < 8; i++) {
        // set bit
        //b = read_bit();
        int byte_loc = pair_pos / 8;
        b = (pair_buffer[byte_loc] >> i) & 1;
        *sym = *sym | (b << i);
        pair_pos += 1;
        // if buffer is full
        if (pair_pos == BLOCK) {
            read_bytes(infile, pair_buffer, BLOCK);
            memset(pair_buffer, 0, BLOCK);
            pair_pos = 0;
        }
    }
    // no more pairs to be read
    if (code == STOP_CODE) {
        return false;
    } else {
        return true;
    }
}

// write word to outfile
void write_word(int outfile, Word *w) {
    // write every symbol to buffer
    for (uint32_t i = 0; i < w->len; i++) {
        // add sym to buff
        sym_buffer[sym_pos] = w->syms[i];
        sym_pos += 1;
        // if buff full, flush buffer
        if (sym_pos == BLOCK) {
            flush_words(outfile);
        }
        total_syms += 1;
    }
}

// write any remaining words to outfile
void flush_words(int outfile) {
    if (sym_pos != 0) {
        write_bytes(outfile, sym_buffer, BLOCK);
        sym_pos = 0;
    }
}
