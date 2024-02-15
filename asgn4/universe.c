// universe.c

#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// define the Universe struct
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

// allocate memory and set struct variables to parameters
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    //allocate for the Universe
    Universe *u = (Universe *) calloc(1, sizeof(Universe));
    // make sure that calloc was successful before proceeding
    if (u) {
        // set rows, cols, and toroidal to parameter
        u->rows = rows;
        u->cols = cols;
        u->toroidal = toroidal;
        // allocate double pointer for grid
        u->grid = (bool **) calloc(rows, sizeof(bool *));
        for (uint32_t r = 0; r < rows; r++) {
            u->grid[r] = (bool *) calloc(cols, sizeof(bool));
        }
    }
    return u;
}

// free and set to null
void uv_delete(Universe *u) {
    // free the grid memory
    for (uint32_t r = 0; r < u->rows; r++) {
        free(u->grid[r]);
    }
    free(u->grid);
    // free Universe and null
    free(u);
    u = NULL;
}

// return rows
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

// return cols
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

// set cell to live
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    // check if it is in the grid
    if ((r < u->rows) && (c < u->cols)) {
        u->grid[r][c] = true;
    }
}

// set cell to dead
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    // check if it is in the grid
    if ((r < u->rows) && (c < u->cols)) {
        u->grid[r][c] = false;
    }
}

// returns value of cell
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    // check if it is in the grid
    if ((r < u->rows) && (c < u->cols)) {
        return u->grid[r][c];
    } else {
        return false;
    }
}

// fills universe from infile
// true if successful, false if not
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t r = 0;
    uint32_t c = 0;
    while (!feof(infile)) {
        // scan the next line
        fscanf(infile, "%" PRIu32 " %" PRIu32 "\n", &r, &c);
        // check in bounds
        if ((r < u->rows) && (c < u->cols)) {
            uv_live_cell(u, r, c);
        } else {
            return false;
        }
    }
    // successful for the whole file
    return true;
}

// return the number of live neighbors
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t count = 0;
    // up
    // if up is around to the other side
    if (u->toroidal && r == 0) {
        if (uv_get_cell(u, u->rows - 1, c)) {
            count++;
        }
    } else if (r != 0) {
        if (uv_get_cell(u, r - 1, c)) {
            count++;
        }
    }
    // down
    // if down is around to the other side
    if (u->toroidal && r == u->rows - 1) {
        if (uv_get_cell(u, 0, c)) {
            count++;
        }
    } else if (r != u->rows - 1) {
        if (uv_get_cell(u, r + 1, c)) {
            count++;
        }
    }
    // left
    // if left is around to the other side
    if (u->toroidal && c == 0) {
        if (uv_get_cell(u, r, u->cols - 1)) {
            count++;
        }
    } else if (c != 0) {
        if (uv_get_cell(u, r, c - 1)) {
            count++;
        }
    }
    // right
    // if right is around to the other side
    if (u->toroidal && c == u->cols - 1) {
        if (uv_get_cell(u, r, 0)) {
            count++;
        }
    } else if (c != u->cols - 1) {
        if (uv_get_cell(u, r, c + 1)) {
            count++;
        }
    }
    // vars for neighbor r and c
    uint32_t nr = 0;
    uint32_t nc = 0;
    // up left
    if (u->toroidal) {
        if (r == 0) {
            nr = u->rows - 1;
        } else {
            nr = r - 1;
        }
        if (c == 0) {
            nc = u->cols - 1;
        } else {
            nc = c - 1;
        }
        if (uv_get_cell(u, nr, nc)) {
            count++;
        }
    } else if ((r != 0) && (c != 0)) {
        if (uv_get_cell(u, r - 1, c - 1)) {
            count++;
        }
    }
    // up right
    if (u->toroidal) {
        if (r == 0) {
            nr = u->rows - 1;
        } else {
            nr = r - 1;
        }
        if (c == u->cols - 1) {
            nc = 0;
        } else {
            nc = c + 1;
        }
        if (uv_get_cell(u, nr, nc)) {
            count++;
        }
    } else if ((r != 0) && (c != u->cols - 1)) {
        if (uv_get_cell(u, r - 1, c + 1)) {
            count++;
        }
    }
    // down left
    if (u->toroidal) {
        if (r == u->rows - 1) {
            nr = 0;
        } else {
            nr = r + 1;
        }
        if (c == 0) {
            nc = u->cols - 1;
        } else {
            nc = c - 1;
        }
        if (uv_get_cell(u, nr, nc)) {
            count++;
        }
    } else if ((r != u->rows - 1) && (c != 0)) {
        if (uv_get_cell(u, r + 1, c - 1)) {
            count++;
        }
    }
    // down right
    if (u->toroidal) {
        if (r == u->rows - 1) {
            nr = 0;
        } else {
            nr = r + 1;
        }
        if (c == u->cols - 1) {
            nc = 0;
        } else {
            nc = c + 1;
        }
        if (uv_get_cell(u, nr, nc)) {
            count++;
        }
    } else if ((r != u->rows - 1) && (c != u->cols - 1)) {
        if (uv_get_cell(u, r + 1, c + 1)) {
            count++;
        }
    }

    return count;
}

// prints the grid to the outfile
void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t r = 0; r < u->rows; r++) {
        for (uint32_t c = 0; c < u->cols; c++) {
            // live cell
            if (uv_get_cell(u, r, c)) {
                fprintf(outfile, "o");
            }
            // dead cell
            else {
                fprintf(outfile, ".");
            }
        }
        fprintf(outfile, "\n");
    }
}
