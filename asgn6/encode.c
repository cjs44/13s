// encode.c

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
            fprintf(stderr, "   Compresses files using the LZ78 compression algorithm.\n");
            fprintf(
                stderr, "   Compressed files are decompressed with the corresponding decoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display compression statistics\n");
            fprintf(stderr, "   -i input    Specify input to compress (stdin by default)\n");
            fprintf(
                stderr, "   -o output   Specify output of compressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program help and usage\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Compresses files using the LZ78 compressionalgorithm.\n");
            fprintf(
                stderr, "   Compressed files are decompressed with the corresponding decoder.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encode [-vh] [-i input] [-o output]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -v          Display compression statistics\n");
            fprintf(stderr, "   -i input    Specify input to compress (stdin by default)\n");
            fprintf(
                stderr, "   -o output   Specify output of compressed input (stdout by default)\n");
            fprintf(stderr, "   -h          Display program help and usage\n");
            return 0;
        }
    }

    // set file header
    FileHeader *header = (FileHeader *) calloc(1, sizeof(FileHeader));
    header->magic = MAGIC;
    // head->protection = ;

    // open outfile
    if (outfile != 1) {
        outfile = open(out, O_CREAT | O_WRONLY);
        if (outfile == -1) {
            fprintf(stderr, "Couldn't open %s: No such file or directory\n", out);
            return 1;
        }
    }

    // write file header
    write_header(outfile, header);

    // initialize trie variables
    TrieNode *root = trie_create();
    TrieNode *curr_node = root;
    TrieNode *prev_node = NULL;
    uint8_t curr_sym = 0;
    uint8_t prev_sym = 0;
    uint16_t next_code = (uint16_t) START_CODE;

    // loop calls to read symbol function
    while (read_sym(infile, &curr_sym)) {
        TrieNode *next_node = trie_step(curr_node, curr_sym);
        if (next_node) {
            prev_node = curr_node;
            curr_node = next_node;
        } else {
            write_pair(outfile, curr_node->code, curr_sym, sizeof(next_code));
            curr_node->children[curr_sym] = trie_node_create(next_code);
            curr_node = root;
            next_code += 1;
        }
        if (next_code == MAX_CODE) {
            trie_reset(root);
            curr_node = root;
            next_code = START_CODE;
        }
        prev_sym = curr_sym;
    }

    // check if current node is at the root
    if (curr_node != root) {
        write_pair(outfile, prev_node->code, prev_sym, sizeof(next_code));
        next_code += 1;
        next_code %= MAX_CODE;
    }

    // write pairs and flush
    write_pair(outfile, STOP_CODE, 0, sizeof(next_code));
    flush_pairs(outfile);

    // print verbose
    if (vf == 1) {
        // compressed
        uint64_t size1 = total_bits / 8;
        // uncompressed
        uint64_t size2 = total_syms;
        // space saving
        double space = 100.0 * (1.0 - ((double) size1 / (double) size2));
        fprintf(stderr, "Compressed file size: %lu bytes\n", size1);
        fprintf(stderr, "Uncompressed file size: %lu bytes\n", size2);
        fprintf(stderr, "Space saving: %.2f%%\n", space);
    }

    //close files
    free(header);
    close(infile);
    close(outfile);

    return 0;
}
