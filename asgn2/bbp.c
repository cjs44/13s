// bbp.c

#include "mathlib.h"

// tracks the number of computed terms
static int count = 0;

// returns the approximate of pi using the BBP formula
double pi_bbp(void) {
    double res = 0.0;
    double prev = 1.0;
    double term = 1.0;
    while (term > EPSILON) {
        double num = count * (120.0 * count + 151.0) + 47.0;
        double den = count * (count * (count * (512.0 * count + 1024.0) + 712.0) + 194.0) + 15.0;
        term = prev * (num / den);
        prev *= 1.0 / 16.0;
        res += term;
        count++;
    }
    return res;
}

// return number of terms
int pi_bbp_terms(void) {
    return count;
}
