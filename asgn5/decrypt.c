// decrypt.c

#include "ss.h"
#include <stdio.h>
#include <gmp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#define OPTIONS "i:o:n:vh"

int main(int argc, char **argv) {
    int opt;
    //initialize default argument values and flags
    FILE *infile = stdin;
    FILE *outfile = stdout;
    FILE *pvfile;
    int pvf = 0;
    int vf = 0;

    //command-line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': //input file
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr,
                    "decrypt: Couldn't open %s to read ciphertext: No such file or directory\n",
                    optarg);
                return 1;
            }
            break;
        case 'o': //output file
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr,
                    "decrypt: Couldn't open %s to write plaintext: No such file or directory\n",
                    optarg);
                return 1;
            }
            break;
        case 'n': //private key file
            pvf = 1;
            pvfile = fopen(optarg, "r");
            if (pvfile == NULL) {
                fprintf(stderr, "./decrypt: couldn't open %s to read private key.\n", optarg);
                return 1;
            }
            break;
        case 'v': //enable verbose
            vf = 1;
            break;
        case 'h': //display help message
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Decrypted data is encrypted by the encrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to decrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for decrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pvfile       Private key file (default: ss.priv).\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Decrypts data using SS decryption.\n");
            fprintf(stderr, "   Decrypted data is encrypted by the encrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./decrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose programoutput.\n");
            fprintf(stderr, "   -i infile       Input file of data to decrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for decrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pvfile       Private key file (default: ss.priv).\n");
            return 0;
        }
    }

    //default for pvfile
    if (pvf == 0) {
        pvfile = fopen("ss.priv", "r");
        if (pvfile == NULL) {
            fprintf(stderr,
                "./decrypt: couldn't open ss.priv to read. Call ./decrypt -h for program usage.\n");
            return 1;
        }
    }

    //reading priv
    mpz_t pq, d;
    mpz_inits(pq, d, NULL);
    ss_read_priv(pq, d, pvfile);

    if (vf == 1) {
        //print verbose
        // pq d
        gmp_fprintf(stderr, "pq (%zu bits) = %Zd\n", mpz_sizeinbase(pq, 2), pq);
        gmp_fprintf(stderr, "d  (%zu bits) = %Zd\n", mpz_sizeinbase(d, 2), d);
    }

    //decrypt
    ss_decrypt_file(infile, outfile, d, pq);

    //clear and close
    fclose(pvfile);
    mpz_clears(pq, d, NULL);
    return 0;
}
