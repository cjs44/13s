// decode.c

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <inttypes.h>
#include "trie.h"
#include "word.h"
#include "io.h"
#include "endian.h"
#include "code.h"

#define OPTIONS "vi:o:h"

int main(int argc, char **argv) {
    int opt;
    //initialize default argument values and flags
    int infile = 0;
    int outfile = 1;
    char *out;
    int vf = 0;

    //command-line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {

        case 'v': // stats print
            vf = 1;
            break;
        case 'i': //input file
            infile = open(optarg, O_RDONLY);
            if (infile == -1) {
                fprintf(stderr, "Couldn't open %s: No such file or directory\n", optarg);
                return 1;
            }
            break;
        case 'o': //output file
            out = optarg;
            break;
        case 'h': //display help message
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decompresses files with the LZ78 decompression algorithm.\n");
            fprintf(stderr, "   Used with files compressed with the corresponding encoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to decompress (stdin by default)\n");
            fprintf(stderr,
                "   -o output   Specify output of decompressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decompresses files with the LZ78 decompression algorithm.\n");
            fprintf(stderr, "   Used with files compressed with the corresponding encoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display decompression statistics\n");
            fprintf(stderr, "   -i input    Specify input to decompress (stdin by default)\n");
            fprintf(stderr,
                "   -o output   Specify output of decompressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program usage\n");
            return 0;
        }
    }

    // read file header
    FileHeader *header = (FileHeader *) calloc(1, sizeof(FileHeader));
    read_header(infile, header);

    // open outfile
    if (outfile != 1) {
        outfile = open(out, header->protection);
        if (outfile == -1) {
            fprintf(stderr, "Couldn't open %s: No such file or directory\n", out);
            return 1;
        }
    }

    // initialize variables
    WordTable *table = wt_create();
    uint8_t curr_sym = 0;
    uint16_t curr_code = 0;
    uint16_t next_code = (uint16_t) START_CODE;

    // loop calls to read pairs
    while (read_pair(infile, &curr_code, &curr_sym, sizeof(next_code))) {
        table[next_code] = word_append_sym(table[curr_code], curr_sym);
        write_word(outfile, table[next_code]);
        next_code += 1;
        if (next_code == MAX_CODE) {
            wt_reset(table);
            next_code = START_CODE;
        }
    }

    // flush words
    flush_words(outfile);

    // print verbose
    if (vf == 1) {
        // compressed
        uint64_t size1 = total_bits / 8;
        // uncompressed
        uint64_t size2 = total_syms;
        // space saving
        double space = 100.0 * (1.0 - ((double) size1 / (double) size2));
        //print verbose
        fprintf(stderr, "Compressed file size: %lu bytes\n", size1);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", size2);
        fprintf(stderr, "Space saving: %.2f%%\n", space);
    }

    // close files
    free(header);
    close(infile);
    close(outfile);

    return 0;
}
