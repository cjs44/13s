// mathlib-test.c

#include "mathlib.h"

#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "aebmrvnsh"

int main(int argc, char **argv) {
    int opt;

    // flags for the cases
    int ef = 0;
    int bf = 0;
    int mf = 0;
    int rf = 0;
    int vf = 0;
    int nf = 0;
    int sf = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            // all tests
            // 'turn on' all test flags
            ef = 1;
            bf = 1;
            mf = 1;
            rf = 1;
            vf = 1;
            nf = 1;
            break;
        case 'e':
            // e approx test
            ef = 1;
            break;
        case 'b':
            // BBP pi
            bf = 1;
            break;
        case 'm':
            // Madhava pi
            mf = 1;
            break;
        case 'r':
            // Euler pi
            rf = 1;
            break;
        case 'v':
            // Viete pi
            vf = 1;
            break;
        case 'n':
            // Newton-Raphson sqrt
            nf = 1;
            break;
        case 's':
            // enable stats
            sf = 1;
            break;
        case 'h':
            // help message
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library\n\n");
            printf("USAGE\n");
            printf("   ./mathlib-test [-aebmrvnsh]\n\n");
            printf("OPTIONS\n");
            printf("  -a   Runs all tests.\n");
            printf("  -e   Runs e test.\n");
            printf("  -b   Runs BBP pi test.\n");
            printf("  -m   Runs Madhava pi test.\n");
            printf("  -r   Runs Euler pi test.\n");
            printf("  -v   Runs Viete pi test.\n");
            printf("  -n   Runs Newton square root tests.\n");
            printf("  -s   Print verbose statistics.\n");
            printf("  -h   Display program synopsis and usage.\n");
            return 0;
        default:
            // help message
            printf("SYNOPSIS\n");
            printf("   A test harness for the small numerical library\n\n");
            printf("USAGE\n");
            printf("   ./mathlib-test [-aebmrvnsh]\n\n");
            printf("OPTIONS\n");
            printf("  -a   Runs all tests.\n");
            printf("  -e   Runs e test.\n");
            printf("  -b   Runs BBP pi test.\n");
            printf("  -m   Runs Madhava pi test.\n");
            printf("  -r   Runs Euler pi test.\n");
            printf("  -v   Runs Viete pi test.\n");
            printf("  -n   Runs Newton square root tests.\n");
            printf("  -s   Print verbose statistics.\n");
            printf("  -h   Display program synopsis and usage.\n");
            return 0;
        }
    }

    // e approximation test
    if (ef) {
        double result = e();
        double lib_result = M_E;
        double diff = absolute(result - lib_result);
        printf("e() = %.15f, M_E = %.15f, diff = %.15f\n", result, lib_result, diff);
        // if stats are enabled, print
        if (sf) {
            printf("e() terms = %d\n", e_terms());
        }
    }

    // BBP pi approximation test
    if (bf) {
        double result = pi_bbp();
        double lib_result = M_PI;
        double diff = absolute(result - lib_result);
        printf("pi_bbp() = %.15f, M_PI = %.15f, diff = %.15f\n", result, lib_result, diff);
        // if stats are enabled, print
        if (sf) {
            printf("pi_bbp() terms = %d\n", pi_bbp_terms());
        }
    }

    // Madhava pi approximation test
    if (mf) {
        double result = pi_madhava();
        double lib_result = M_PI;
        double diff = absolute(result - lib_result);
        printf("pi_madhava() = %.15f, M_PI = %.15f, diff = %.15f\n", result, lib_result, diff);
        // if stats are enabled, print
        if (sf) {
            printf("pi_madhava() terms = %d\n", pi_madhava_terms());
        }
    }

    // Euler sequence pi approximation test
    if (rf) {
        double result = pi_euler();
        double lib_result = M_PI;
        double diff = absolute(result - lib_result);
        printf("pi_euler() = %.15f, M_PI = %.15f, diff = %.15f\n", result, lib_result, diff);
        // if stats are enabled, print
        if (sf) {
            printf("pi_euler() terms = %d\n", pi_euler_terms());
        }
    }

    // Viete pi approximation test
    if (vf) {
        double result = pi_viete();
        double lib_result = M_PI;
        double diff = absolute(result - lib_result);
        printf("pi_viete() = %.15f, M_PI = %.15f, diff = %.15f\n", result, lib_result, diff);
        // if stats are enabled, print
        if (sf) {
            printf("pi_viete() terms = %d\n", pi_viete_factors());
        }
    }

    // Newton-Raphson square root approximation test
    if (nf) {
        for (double i = 0.0; i <= 10.0; i += 0.1) {
            double result = sqrt_newton(i);
            double lib_result = sqrt(i);
            double diff = absolute(result - lib_result);
            printf("sqrt_newton(%.6f) = %.15f, sqrt(%.6f) = %.15f, diff = %.15f\n", i, result, i,
                lib_result, diff);
            // if stats are enabled, print
            if (sf) {
                printf("sqrt_newton() terms = %d\n", sqrt_newton_iters());
            }
        }
    }

    return 0;
}
