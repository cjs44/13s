// keygen.c
// generates new public and private keys

#include "ss.h"
#include "randstate.h"
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>

#define OPTIONS "b:i:n:d:s:vh"

int main(int argc, char **argv) {
    int opt;
    //initialize default argument values and flags
    uint64_t min_bits = 256;
    uint64_t iters = 50;
    FILE *pbfile;
    int pbf = 0;
    FILE *pvfile;
    int pvf = 0;
    uint64_t seed = time(NULL);
    int vf = 0;
    //command-line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': //minimum bits
            min_bits = atoi(optarg);
            break;
        case 'i': //iterations
            iters = atoi(optarg);
            break;
        case 'n': //public key file
            pbf = 1;
            pbfile = fopen(optarg, "w");
            if (pbfile == NULL) {
                fprintf(stderr, "./keygen: couldn't open %s to write public key.\n", optarg);
                return 1;
            }
            break;
        case 'd': //private key file
            pvf = 1;
            pvfile = fopen(optarg, "w");
            if (pvfile == NULL) {
                fprintf(stderr, "./keygen: couldn't open %s to write private key.\n", optarg);
                return 1;
            }
            break;
        case 's': //seed
            seed = atoi(optarg);
            break;
        case 'v': //enable verbose
            vf = 1;
            break;
        case 'h': //display help message
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr,
                "   -b bits         Minimum bits needed for public key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterations for testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Generates an SS public/private key pair.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./keygen [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose programoutput.\n");
            fprintf(
                stderr, "   -b bits         Minimum bits needed forpublic key n (default: 256).\n");
            fprintf(stderr,
                "   -i iterations   Miller-Rabin iterationsfor testing primes (default: 50).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            fprintf(stderr, "   -d pvfile       Private key file (default: ss.priv).\n");
            fprintf(stderr, "   -s seed         Random seed for testing.\n");
            return 0;
        }
    }

    // open defaults for the public and private files
    if (pbf == 0) {
        pbfile = fopen("ss.pub", "w");
        if (pbfile == NULL) {
            fprintf(stderr, "./keygen: couldn't open ss.pub to write public key. Call ./keygen -h "
                            "for program usage.\n");
            return 1;
        }
    }
    if (pvf == 0) {
        pvfile = fopen("ss.priv", "w");
        if (pvfile == NULL) {
            fprintf(stderr, "./keygen: couldn't open ss.priv to write private key. Call ./keygen "
                            "-h for program usage.\n");
            return 1;
        }
    }

    //set the correct permissions for the private file
    int fn = fileno(pvfile);
    fchmod(fn, S_IRUSR | S_IWUSR);

    //random state
    randstate_init(seed);

    //make the keys
    mpz_t p, q, n, d, pq;
    mpz_inits(p, q, n, d, pq, NULL);
    ss_make_pub(p, q, n, min_bits, iters);
    ss_make_priv(d, pq, p, q);

    //get username from the environment
    char *username;
    username = getenv("USER");

    //write to public and private files
    ss_write_pub(n, username, pbfile);
    ss_write_priv(pq, d, pvfile);

    if (vf == 1) {
        //print verbose
        // username, p, q, n, d, pq
        gmp_fprintf(stderr, "user: %s\n", username);
        gmp_fprintf(stderr, "p  (%zu bits) = %Zd\n", mpz_sizeinbase(p, 2), p);
        gmp_fprintf(stderr, "q  (%zu bits) = %Zd\n", mpz_sizeinbase(q, 2), q);
        gmp_fprintf(stderr, "n  (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
        gmp_fprintf(stderr, "d  (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
        gmp_fprintf(stderr, "pq (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
    }

    //clear and close
    fclose(pbfile);
    fclose(pvfile);
    randstate_clear();
    mpz_clears(p, q, n, d, pq, NULL);
    return 0;
}
