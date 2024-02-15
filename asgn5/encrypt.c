// encrypt.c

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
    FILE *pbfile;
    int pbf = 0;
    int vf = 0;

    //command-line
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': //input file
            infile = fopen(optarg, "r");
            if (infile == NULL) {
                fprintf(stderr,
                    "encrypt: Couldn't open %s to read plaintext: No such file or directory\n",
                    optarg);
                return 1;
            }
            break;
        case 'o': //output file
            outfile = fopen(optarg, "w");
            if (outfile == NULL) {
                fprintf(stderr,
                    "encrypt: Couldn't open %s to write ciphertext: No such file or directory\n",
                    optarg);
                return 1;
            }
            break;
        case 'n': //public key file
            pbf = 1;
            pbfile = fopen(optarg, "r");
            if (pbfile == NULL) {
                fprintf(stderr, "./encrypt: couldn't open %s to read public key.\n", optarg);
                return 1;
            }
            break;
        case 'v': //enable verbose
            vf = 1;
            break;
        case 'h': //display help message
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose program output.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 0;
        default:
            fprintf(stderr, "SYNOPSIS\n");
            fprintf(stderr, "   Encrypts data using SS encryption.\n");
            fprintf(stderr, "   Encrypted data is decrypted by the decrypt program.\n\n");
            fprintf(stderr, "USAGE\n");
            fprintf(stderr, "   ./encrypt [OPTIONS]\n\n");
            fprintf(stderr, "OPTIONS\n");
            fprintf(stderr, "   -h              Display program help and usage.\n");
            fprintf(stderr, "   -v              Display verbose programoutput.\n");
            fprintf(stderr, "   -i infile       Input file of data to encrypt (default: stdin).\n");
            fprintf(
                stderr, "   -o outfile      Output file for encrypted data (default: stdout).\n");
            fprintf(stderr, "   -n pbfile       Public key file (default: ss.pub).\n");
            return 0;
        }
    }

    //default for the pbfile
    if (pbf == 0) {
        pbfile = fopen("ss.pub", "r");
        if (pbfile == NULL) {
            fprintf(stderr,
                "./encrypt: couldn't open ss.pub to read. Call ./encrypt -h for program usage.\n");
            return 1;
        }
    }

    //reading pub
    mpz_t n;
    mpz_init(n);
    char username[32]; //can only be this long
    ss_read_pub(n, username, pbfile);

    if (vf == 1) {
        //print verbose
        gmp_fprintf(stderr, "user = %s\n", username);
        gmp_fprintf(stderr, "n (%zu bits) = %Zd\n", mpz_sizeinbase(n, 2), n);
    }

    //encrypt
    ss_encrypt_file(infile, outfile, n);

    //clear and close
    fclose(pbfile);
    mpz_clear(n);
    return 0;
}
