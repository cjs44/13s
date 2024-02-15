// euler.c

#include "mathlib.h"

// track the computed terms
static int count = 0;

// returns the approximate of pi using Euler's solution
double pi_euler(void) {
    double term = 1.0;
    double res = 0.0;
    while (term > EPSILON) {
        count++;
        term = 1.0 / (double) (count * count);
        res += term;
    }
    return sqrt_newton(6.0 * res);
}

//return number of terms
int pi_euler_terms(void) {
    return count;
}
