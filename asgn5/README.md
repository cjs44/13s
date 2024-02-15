# README Assignment 5
## Caitlin Smith - csmith44 - 2/26/23

In order to run my Assignment 5 programs, download the files and start with *make clean* and *make all*.<br>
Enter *./keygen* with any of the command line-options (b:i:n:d:s:vh). If the cases with arguments are not called, the code will run with the default values.<br>
Enter *./encrypt* with any of the command line-options (i:o:n:vh). If the cases with arguments are not called, the code will run with the default values.<br>
Enter *./decrypt* with any of the command line-options (i:o:n:vh). If the cases with arguments are not called, the code will run with the default values.<br>

**Command-line Options for Keygen**<br>
*-b* will specify the minimum number of bits needed for the public modulus n (default of 256)<br>
*-i* will specify the number of Miller-Rabin iterations for testing primes (default of 50)<br>
*-n* will specify the public key file (default of ss.pub)<br>
*-d* will specify the private key file (default of ss.priv)<br>
*-s* will specify the random seed for the random state initialization (default of seconds since the unix epoch)<br>
*-v* will enable the verbose output<br>
*-h* will display the program synopsis and usage<br>
**Command-line Options for Encrypt**<br>
*-i* will specify the input file to encrpyt (default of stdin)<br>
*-o* will specify the output file to encrypt (default of stdout)<br>
*-n* will specify the file containing the public key (default of ss.pub)<br>
*-v* will enable the verbose output<br>
*-h* will display the program synopsis and usage<br>
**Command-line Options for Decrypt**<br>
*-i* will specify the input file to decrpyt (default of stdin)<br>
*-o* will specify the output file to decrypt (default of stdout)<br>
*-n* will specify the file containing the private key (default of ss.priv)<br>
*-v* will enable the verbose output<br>
*-h* will display the program synopsis and usage<br>

**Files**<br>
*decrypt.c* contains the implementation and main() function for the decrypt program<br>
*encrypt.c* contains the implementation and main() function for the encrypt program<br>
*keygen.c* contains the implementation and main() function for the keygen program<br>
*numtheory.c* implements the number theory functions<br>
*numtheory.h* specifies the interface to numtheory.c<br>
*randstate.c* implements the random state interface for the SS library<br>
*randstate.h* specifies the interface to randstate.c<br>
*ss.c* implements the SS library<br>
*ss.h* specifies the interface for ss.c<br>
*Makefile* contains what is needed to clear and recompile<br>
*README.md* describes how to use the program and details parts of it<br>
*DESIGN.pdf* describes the design and process enough to be replicated<br>
*WRITEUP.pdf* includes the necessary analysis of the program<br>

**Resources**<br>
I searched through existing Discord questions and discussions in order to debug various parts of my code. For example, I had issues with how to get the log of square root n. I also watched a video about decryption and encryption to help me understand the concept more thoroughly. I also utilized the gmplib.org manual.
