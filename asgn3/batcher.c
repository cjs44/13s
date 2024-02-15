// batcher.c

#include "batcher.h"

#include "stats.h"

#include <stdio.h>

// helper function to compare and swap indices
void comparator(Stats *stats, uint32_t *arr, uint32_t x, uint32_t y) {
    if (cmp(stats, arr[x], arr[y]) == 1) {
        swap(stats, &arr[x], &arr[y]);
    }
}

// sorts the passed array using batcher sort
// tracks stats
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t len = n;
    uint32_t t = 0;
    while (len) {
        t += 1;
        len /= 2;
    }
    uint32_t p = 1 << (t - 1);
    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;
        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = (q - p);
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
