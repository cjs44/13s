// life.c

#include "universe.h"

#include <inttypes.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "tsn:i:o:h"
#define DELAY   50000

int main(int argc, char **argv) {
    int opt;
    // initialize default argument values and flags
    uint32_t generations = 100;
    FILE *infile = stdin;
    FILE *outfile = stdout;
    bool tf = 0;
    bool sf = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': // toroidal
            tf = 1;
            break;
        case 's': // silence ncurses
            sf = 1;
            break;
        case 'n': // number of generations
            generations = atoi(optarg);
            break;
        case 'i': // set infile
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr, "Error opening the file.");
                return 1;
            }
            break;
        case 'o': // set outfile
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr, "Error opening the file.");
                return 1;
            }
            break;
        case 'h': // print help message
            printf("SYNOPSIS\n");
            printf("    Conway's Game of Life\n\n");
            printf("USAGE\n");
            printf("    ./life tsn:i:o:h\n\n");
            printf("OPTIONS\n");
            printf("    -t             Create your universe as a toroidal\n");
            printf("    -s             Silent - do not use animate the evolution\n");
            printf("    -n {number}    Number of generations [default: 100]\n");
            printf("    -i {file}      Input file [default: stdin]\n");
            printf("    -o {file}      Output file [default: stdout]\n");
            return 0;
        default: // print help message
            printf("SYNOPSIS\n");
            printf("    Conway's Game of Life\n\n");
            printf("USAGE\n");
            printf("    ./life tsn:i:o:h\n\n");
            printf("OPTIONS\n");
            printf("    -t             Create your universe as a toroidal\n");
            printf("    -s             Silent - do not use animate the evolution\n");
            printf("    -n {number}    Number of generations [default: 100]\n");
            printf("    -i {file}      Input file [default: stdin]\n");
            printf("    -o {file}      Output file [default: stdout]\n");
            return 0;
        }
    }

    // read the first line of infile to get rows and cols
    uint32_t row = 0;
    uint32_t col = 0;
    fscanf(infile, "%" PRIu32 " %" PRIu32 "\n", &row, &col);

    // create Universes A and B
    Universe *A = uv_create(row, col, tf);
    Universe *B = uv_create(row, col, tf);

    // fill Universe A
    if (!uv_populate(A, infile)) {
        uv_delete(A);
        uv_delete(B);
        fprintf(stderr, "Malformed input.\n");
        return 1;
    }

    // set up ncurses
    if (!sf) {
        initscr();
        curs_set(FALSE);
    }

    //temp universe for swapping later
    Universe *temp = uv_create(row, col, tf);

    // loop for specified generations
    for (uint32_t g = 0; g < generations; g++) {
        // call the census function for each cell
        // make moves based on the rules
        // display Universe A if desired
        uint32_t count = 0;
        for (uint32_t r = 0; r < uv_rows(A); r++) {
            for (uint32_t c = 0; c < uv_cols(A); c++) {
                count = uv_census(A, r, c);
                // live cell with 2 or 3 live neighbors, survives
                if (uv_get_cell(A, r, c) && (count == 2 || count == 3)) {
                    uv_live_cell(B, r, c);
                }
                // dead cell with 3 live neighbors, is live
                else if (!uv_get_cell(A, r, c) && count == 3) {
                    uv_live_cell(B, r, c);
                }
                // else, cell dies
                else {
                    uv_dead_cell(B, r, c);
                }
                // display
                if (!sf) {
                    if (uv_get_cell(A, r, c)) {
                        mvprintw(r, c, "o");
                    } else {
                        mvprintw(r, c, " ");
                    }
                }
            }
        }

        // refresh display
        usleep(DELAY);
        refresh();

        // swap the Universes
        temp = A;
        A = B;
        B = temp;

        // clear
        clear();
    }

    // close the screen
    endwin();

    // print A to the outfile
    uv_print(A, outfile);

    // free and close
    fclose(infile);
    fclose(outfile);
    uv_delete(A);
    uv_delete(B);

    return 0;
}
