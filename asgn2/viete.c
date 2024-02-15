// viete.c

#include "mathlib.h"

//static var for tracking factors
static int count = 0;

// returns the approximation of pi using Viete's formula
double pi_viete(void) {
    double prev = 0.0;
    double curr = 0.0;
    double term = 1.0;
    double res = 1.0;
    while (absolute((prev / 2.0) - term) > EPSILON) {
        prev = curr;
        curr = sqrt_newton(2.0 + prev);
        term = curr / 2.0;
        res *= term;
        count++;
    }
    return (2.0 / res);
}

// return number of factors
int pi_viete_factors(void) {
    return count;
}
