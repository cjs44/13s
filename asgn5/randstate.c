// randstate.c

#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <stdint.h>
#include <stdlib.h>

// declare state variable (already declared extern)
gmp_randstate_t state;

// initialize with the given seed
void randstate_init(uint64_t seed) {
    srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
}

// function to free memory
void randstate_clear(void) {
    gmp_randclear(state);
}
