// newton.c

#include "mathlib.h"

// track the number of iterations
static int count = 0;

// returns the approximation of the sqrt using Newton-Raphson
double sqrt_newton(double x) {
    // reset the count to 0
    count = 0;
    double z = 0.0;
    double y = 1.0;
    while (absolute(y - z) > EPSILON) {
        count++;
        z = y;
        y = 0.5 * (z + x / z);
    }
    return y;
}

// return number of iterations
int sqrt_newton_iters(void) {
    return count;
}
