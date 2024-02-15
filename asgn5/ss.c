// ss.c

#include "ss.h"
#include "numtheory.h"
#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

//  create a new public key
void ss_make_pub(mpz_t p, mpz_t q, mpz_t n, uint64_t nbits, uint64_t iters) {
    // find p and q num of bits
    uint64_t pbits = random() % ((2 * nbits) / 5 + 1 - (nbits / 5) + 1) + (nbits / 5);
    uint64_t qbits = nbits - (pbits * 2);
    // create primes p and q
    make_prime(p, pbits, iters);
    make_prime(q, qbits, iters);
    // n = ppq
    mpz_mul(n, p, p);
    mpz_mul(n, n, q);
    // loop for log2(n) >= nbits
    while (mpz_sizeinbase(n, 2) >= nbits) {
        make_prime(p, pbits, iters);
        make_prime(q, qbits, iters);
        // n = ppq
        mpz_mul(n, p, p);
        mpz_mul(n, n, q);
    }
}

// create a new private key
void ss_make_priv(mpz_t d, mpz_t pq, const mpz_t p, const mpz_t q) {
    //temps
    mpz_t pt, qt, num, gcd_res, lcm, abs;
    mpz_inits(pt, qt, num, gcd_res, lcm, abs, NULL);
    // calculate lambda pq
    // = lcm(p-1, q-1)
    // = (p-1)(q-1) / gcd(p-1, q-1)
    mpz_sub_ui(pt, p, 1);
    mpz_sub_ui(qt, q, 1);
    mpz_mul(num, pt, qt);
    mpz_abs(abs, num);
    gcd(gcd_res, pt, qt);
    mpz_fdiv_q(lcm, abs, gcd_res);
    // inverse of n mod lambda pq
    mpz_t n;
    mpz_init_set(n, p);
    mpz_mul(n, n, p);
    mpz_mul(n, n, q);
    mod_inverse(d, n, lcm);
    mpz_clears(pt, qt, num, gcd_res, lcm, abs, n, NULL);
    // pq
    mpz_mul(pq, p, q);
}

// write public key to file
void ss_write_pub(const mpz_t n, const char username[], FILE *pbfile) {
    // print n and username
    gmp_fprintf(pbfile, "%Zx\n%s\n", n, username);
}

// write private key to file
void ss_write_priv(const mpz_t pq, const mpz_t d, FILE *pvfile) {
    // print pq and d
    gmp_fprintf(pvfile, "%Zx\n%Zx\n", pq, d);
}

// read public key from file
void ss_read_pub(mpz_t n, char username[], FILE *pbfile) {
    // scan n and username
    gmp_fscanf(pbfile, "%Zx\n%s\n", n, username);
}

// read private key from file
void ss_read_priv(mpz_t pq, mpz_t d, FILE *pvfile) {
    // scan pq and d
    gmp_fscanf(pvfile, "%Zx\n%Zx\n", pq, d);
}

// perform encryption with pow_mod
// ciphertext c
// message m
// public key n
void ss_encrypt(mpz_t c, const mpz_t m, const mpz_t n) {
    pow_mod(c, m, n, n);
}

// encrypt infile, writing to outfile
void ss_encrypt_file(FILE *infile, FILE *outfile, const mpz_t n) {
    // create temps
    mpz_t m, c;
    mpz_inits(m, c, NULL);
    //block size
    size_t k = (mpz_sizeinbase(n, 2) / 2 - 1) / 8;
    //allocate for array
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));
    //set zero most byte to 0xff
    arr[0] = 0xFF;
    // var for bytes read
    size_t j;
    // loop to read and print
    while ((j = fread(arr + 1, sizeof(uint8_t), k - 1, infile)) > 0) {
        mpz_import(m, j + 1, 1, sizeof(uint8_t), 1, 0, arr);
        ss_encrypt(c, m, n);
        gmp_fprintf(outfile, "%Zx\n", c);
    }
    // free and clear
    free(arr);
    fclose(outfile);
    fclose(infile);
    mpz_clears(c, m, NULL);
}

// perform decryption with pow_mod
// message m
// ciphertext c
// private key d
// public mod pq
void ss_decrypt(mpz_t m, const mpz_t c, const mpz_t d, const mpz_t pq) {
    pow_mod(m, c, d, pq);
}

// decrypt infile, write to outfile
void ss_decrypt_file(FILE *infile, FILE *outfile, const mpz_t d, const mpz_t pq) {
    // temp vars
    mpz_t c, m;
    mpz_inits(c, m, NULL);
    //block size
    size_t k = (mpz_sizeinbase(pq, 2) - 1) / 8;
    //allocate for array
    uint8_t *arr = (uint8_t *) calloc(k, sizeof(uint8_t));
    size_t j;
    // loop to read and write
    while (!feof(infile)) {
        gmp_fscanf(infile, "%Zx\n", c);
        ss_decrypt(m, c, d, pq);
        mpz_export(arr, &j, 1, sizeof(uint8_t), 1, 0, m);
        fwrite(arr + 1, sizeof(uint8_t), j - 1, outfile);
    }
    // free and clear
    free(arr);
    fclose(infile);
    fclose(outfile);
    mpz_clears(c, m, NULL);
}
