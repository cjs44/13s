// e.c

#include "mathlib.h"

// tracks the number of terms
static int count = 0;

// returns the approximate value of e
double e(void) {
    double prev = 1.0;
    double curr = 1.0;
    //set res to 1 to account for the very first term 1
    double res = 1.0;
    while (curr > EPSILON) {
        count++;
        curr = prev * 1.0 / count;
        prev = curr;
        res += curr;
    }
    // increase count by 1 to acccount for the first term 1
    count++;
    return res;
}

// return the number of terms
int e_terms(void) {
    return count;
}
