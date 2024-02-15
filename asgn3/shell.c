// shell.c

#include "shell.h"

#include "gaps.h"
#include "stats.h"

#include <stdio.h>

// uses the shell sort method to sort the passed array pointer
// tracks stats using stats functions to make moves and compares
void shell_sort(Stats *stats, uint32_t *arr, uint32_t length) {
    // iterate the gaps array
    for (uint32_t g = 0; g < GAPS; g++) {
        uint32_t gap = gaps[g];
        for (uint32_t i = gap; i < length; i++) {
            uint32_t j = i;
            uint32_t temp = move(stats, arr[i]);
            while (j >= gap && (cmp(stats, temp, arr[j - gap]) == -1)) {
                arr[j] = move(stats, arr[j - gap]);
                j -= gap;
            }
            arr[j] = move(stats, temp);
        }
    }
}
