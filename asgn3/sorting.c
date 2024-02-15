// sorting.c

#include "batcher.h"
#include "heap.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "ahbsqr:n:p:H"

int main(int argc, char **argv) {
    int opt;
    // initialize default argument values
    uint64_t seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100;
    // make set for tracking command-line
    Set s = set_empty();

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': // heap sort
            s = set_insert(s, 1);
            break;
        case 'b': // batcher sort
            s = set_insert(s, 2);
            break;
        case 's': // shell sort
            s = set_insert(s, 3);
            break;
        case 'q': //quick sort
            s = set_insert(s, 4);
            break;
        case 'a': // all sorts
            s = set_universal();
            break;
        case 'r': // set seed to arg
            seed = atoi(optarg);
            break;
        case 'n': // set array size to arg
            size = atoi(optarg);
            break;
        case 'p': // set elements to print to arg
            elements = atoi(optarg);
            break;
        case 'H': // print help message
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -n length       Specify number of array elements(default: 100).\n");
            printf("   -p elements     Specify number of elements to print (default: 100).\n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            return 0;
        default: // print help message
            printf("SYNOPSIS\n");
            printf("   A collection of comparison-based sorting algorithms.\n\n");
            printf("USAGE\n");
            printf("   ./sorting [-Hasbhqn:p:r:] [-n length] [-p elements] [-r seed]\n\n");
            printf("OPTIONS\n");
            printf("   -H              Display program help and usage.\n");
            printf("   -a              Enable all sorts.\n");
            printf("   -s              Enable Shell Sort.\n");
            printf("   -b              Enable Batcher Sort.\n");
            printf("   -h              Enable Heap Sort.\n");
            printf("   -q              Enable Quick Sort.\n");
            printf("   -n length       Specify number of array elements (default: 100).\n");
            printf("   -p elements     Specify number of elements to print (default: 100).\n");
            printf("   -r seed         Specify random seed (default: 13371453).\n");
            return 0;
        }
    }

    // heap sort
    if (set_member(s, 1)) {
        //allocate
        Stats *stats = (Stats *) calloc(1, sizeof(Stats));
        uint32_t *arr = (uint32_t *) calloc(size, sizeof(uint32_t));
        srand(seed);
        // fill with random numbers
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = rand() & 0x3FFFFFFF;
        }
        reset(stats);
        // call sort
        heap_sort(stats, arr, size);
        printf("Heap Sort, %u elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        // if the desired print is bigger than the arr print the full arr
        if (size < elements) {
            elements = size;
        }
        for (uint32_t i = 0; i < elements; i++) {
            printf("%13" PRIu32, arr[i]);
            // new line after five prints
            if (((i + 1) % 5) == 0 && i != elements - 1) {
                printf("\n");
            }
        }
        printf("\n");
        free(stats);
        free(arr);
    }

    // batcher sort
    if (set_member(s, 2)) {
        //allocate
        Stats *stats = (Stats *) calloc(1, sizeof(Stats));
        uint32_t *arr = (uint32_t *) calloc(size, sizeof(uint32_t));
        srand(seed);
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = rand() & 0x3FFFFFFF;
        }
        reset(stats);
        batcher_sort(stats, arr, size);
        printf("Batcher Sort, %u elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        // if the desired print is bigger than the array
        if (size < elements) {
            elements = size;
        }
        for (uint32_t i = 0; i < elements; i++) {
            printf("%13" PRIu32, arr[i]);
            if (((i + 1) % 5) == 0 && i != elements - 1) {
                printf("\n");
            }
        }
        printf("\n");
        free(stats);
        free(arr);
    }

    // shell sort
    if (set_member(s, 3)) {
        //allocate
        Stats *stats = (Stats *) calloc(1, sizeof(Stats));
        uint32_t *arr = (uint32_t *) calloc(size, sizeof(uint32_t));
        srand(seed);
        //fill with numbers
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = rand() & 0x3FFFFFFF;
        }
        reset(stats);
        // call sort
        shell_sort(stats, arr, size);
        printf("Shell Sort, %u elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        // if the desired print is bigger than the array
        if (size < elements) {
            elements = size;
        }
        for (uint32_t i = 0; i < elements; i++) {
            printf("%13" PRIu32, arr[i]);
            // new line after five
            if (((i + 1) % 5) == 0 && i != elements - 1) {
                printf("\n");
            }
        }
        printf("\n");
        free(stats);
        free(arr);
    }

    // quick  sort
    if (set_member(s, 4)) {
        //allocate
        Stats *stats = (Stats *) calloc(1, sizeof(Stats));
        uint32_t *arr = (uint32_t *) calloc(size, sizeof(uint32_t));
        srand(seed);
        // fill with numbers
        for (uint32_t i = 0; i < size; i++) {
            arr[i] = rand() & 0x3FFFFFFF;
        }
        reset(stats);
        //call sort
        quick_sort(stats, arr, size);
        printf("Quick Sort, %u elements, %lu moves, %lu compares\n", size, stats->moves,
            stats->compares);
        // if the desired print is bigger than the array
        if (size < elements) {
            elements = size;
        }
        for (uint32_t i = 0; i < elements; i++) {
            printf("%13" PRIu32, arr[i]);
            // new line after five
            if (((i + 1) % 5) == 0 && i != elements - 1) {
                printf("\n");
            }
        }
        printf("\n");
        free(stats);
        free(arr);
    }

    return 0;
}
