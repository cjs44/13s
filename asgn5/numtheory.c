// numtheory.c

#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>

// compute greatest common divisor of a and b, stored to g
void gcd(mpz_t g, const mpz_t a, const mpz_t b) {
    // create temp variable
    mpz_t at, bt, t;
    mpz_init_set(at, a);
    mpz_init_set(bt, b);
    while (mpz_cmp_ui(bt, 0) != 0) {
        mpz_init_set(t, bt);
        mpz_mod(bt, at, bt);
        mpz_set(at, t);
    }
    mpz_set(g, t);
    // clear temos
    mpz_clears(at, bt, t, NULL);
}

// modular inverse
void mod_inverse(mpz_t o, const mpz_t a, const mpz_t n) {
    // create r, t, and primes
    mpz_t r, rp, t, tp;
    mpz_init_set(r, n);
    mpz_init_set(rp, a);
    mpz_init_set_ui(t, 0);
    mpz_init_set_ui(tp, 1);

    while (mpz_cmp_ui(rp, 0) != 0) {
        // create temp variables
        mpz_t rt, rpt, tt, tpt;
        mpz_init_set(rt, r);
        mpz_init_set(rpt, rp);
        mpz_init_set(tt, t);
        mpz_init_set(tpt, tp);
        mpz_t q, mul1, mul2;
        mpz_inits(q, mul1, mul2, NULL);
        // calculate q
        mpz_fdiv_q(q, r, rp); //q = r/rp
        // set r and rp
        mpz_set(r, rpt);
        mpz_mul(mul1, q, rpt);
        mpz_sub(rp, rt, mul1);
        // set t and tp
        mpz_set(t, tpt);
        mpz_mul(mul2, q, tpt);
        mpz_sub(tp, tt, mul2);
        //clear the temps (it clears every loop)
        mpz_clears(q, rt, rpt, tt, tpt, mul1, mul2, NULL);
    }
    if (mpz_cmp_ui(r, 1) > 0) {
        mpz_set(t, 0);
    }
    if (mpz_cmp_ui(t, 0) < 0) {
        mpz_add(t, t, n);
    }
    // set output and clear temps
    mpz_set(o, t);
    mpz_clears(r, rp, t, tp, NULL);
}

// power mod
// a is the base
// d is the exponent
// n is the modulus
void pow_mod(mpz_t o, const mpz_t a, const mpz_t d, const mpz_t n) {
    mpz_t v, p, dt;
    mpz_init_set_ui(v, 1);
    mpz_init_set(p, a);
    mpz_init_set(dt, d);
    while (mpz_cmp_ui(dt, 0) > 0) {
        if (mpz_odd_p(dt) != 0) {
            mpz_mul(v, v, p);
            mpz_mod(v, v, n);
        }
        mpz_mul(p, p, p);
        mpz_mod(p, p, n);
        mpz_fdiv_q_ui(dt, dt, 2);
    }
    // set output and clear
    mpz_set(o, v);
    mpz_clears(v, p, dt, NULL);
}

// Miller-Rabin test to indicate whether n is prime or not
bool is_prime(const mpz_t n, uint64_t iters) {
    // check special cases
    //n is less than 2, false
    if (mpz_cmp_ui(n, 2) < 0) {
        return false;
    }
    //n is 2, true
    if (mpz_cmp_ui(n, 2) == 0) {
        return true;
    }
    //n is 3, true
    if (mpz_cmp_ui(n, 3) == 0) {
        return true;
    }
    //n is even, false
    if (mpz_even_p(n) != 0) {
        return false;
    }

    // n - 1 = 2^s * r, such that r is odd
    mpz_t s, r;
    mpz_init(s);
    mpz_init_set(r, n);
    mpz_sub_ui(r, r, 1);
    while (mpz_even_p(r) != 0) {
        mpz_fdiv_q_ui(r, r, 2);
        mpz_add_ui(s, s, 1);
    }

    for (uint64_t i = 1; i <= iters; i++) {
        //temps
        mpz_t a, y, j, two, n_sub_one, n_sub_three, s_sub_one;
        mpz_inits(a, y, j, two, n_sub_one, n_sub_three, s_sub_one, NULL);
        mpz_set_ui(two, 2);
        mpz_sub_ui(n_sub_one, n, 1);
        mpz_sub_ui(n_sub_three, n, 3);
        mpz_sub_ui(n_sub_one, n, 1);
        //choose random in range 2 to n - 2
        mpz_urandomm(a, state, n_sub_three);
        mpz_add_ui(a, a, 2);
        pow_mod(y, a, r, n);

        if (mpz_cmp_ui(y, 1) != 0 && mpz_cmp(y, n_sub_one) != 0) {
            mpz_set_ui(j, 1);
            while (mpz_cmp(j, s_sub_one) <= 0 && mpz_cmp(y, n_sub_one) != 0) {
                pow_mod(y, y, two, n);
                if (mpz_cmp_ui(y, 1) == 0) {
                    mpz_clears(s, r, a, y, j, two, n_sub_one, n_sub_three, s_sub_one, NULL);
                    return false;
                }
                mpz_add_ui(j, j, 1);
            }
            if (mpz_cmp(y, n_sub_one) != 0) {
                mpz_clears(s, r, a, y, j, two, n_sub_one, n_sub_three, s_sub_one, NULL);
                return false;
            }
        }
        mpz_clears(a, y, j, two, n_sub_one, n_sub_three, s_sub_one, NULL);
    }
    mpz_clears(s, r, NULL);
    return true;
}

// generate a new prime p of at least bits length
void make_prime(mpz_t p, uint64_t bits, uint64_t iters) {
    mpz_urandomb(p, state, bits);
    while (mpz_sizeinbase(p, 2) < bits || mpz_even_p(p) != 0) {
        mpz_urandomb(p, state, bits);
    }
    while (is_prime(p, iters) == 0) {
        mpz_urandomb(p, state, bits);
        while (mpz_sizeinbase(p, 2) < bits || mpz_even_p(p) != 0) {
            mpz_urandomb(p, state, bits);
        }
    }
}
