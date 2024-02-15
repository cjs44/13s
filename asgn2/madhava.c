// madhava.c

#include "mathlib.h"

// tracks the number of terms
static int count = 0;

// returns the approximation of pi using the Madhava series
double pi_madhava(void) {
    double prev = 0.0;
    double curr = 1.0;
    double term = 1.0;
    double res = 0.0;
    while (absolute(term) > EPSILON) {
        term = curr * (1.0 / ((2.0 * count) + 1.0));
        res += term;
        prev = curr;
        curr = prev * 1.0 / -3.0;
        count++;
    }
    return res * sqrt_newton(12.0);
}

// return number of terms
int pi_madhava_terms(void) {
    return count;
}
