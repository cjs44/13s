# README Assignment 6
## Caitlin Smith - csmith44 - 3/12/23

In order to run my Assignment 6 programs, download the files and start with *make clean* and *make all*.<br>
Enter *./encode* with any of the command line-options (vi:o:h). If the cases with arguments are not called, the code will run with the default values. LZ78 compression is performed.<br>
Enter *./decode* with any of the command line-options (vi:o:h). If the cases with arguments are not called, the code will run with the default values. LZ78 decompression is performed.<br>

**Command-line Options for Encrypt**<br>
*-v* will enable the compression statistics<br>
*-i* will specify the input file to compress (default of stdin)<br>
*-o* will specify the output file for the compressed input (default of stdout)<br>
*-h* will display the program synopsis and usage<br>
**Command-line Options for Decrypt**<br>
*-v* will enable the decompression statistics<br>
*-i* will specify the input file to decompress (default of stdin)<br>
*-o* will specify the output file for the decompressed input (default of stdout)<br>
*-h* will display the program synopsis and usage<br>

**Files**<br>
*encode.c* contains the implementation and main() function for the decompression program<br>
*decode.c* contains the implementation and main() function for the compression program<br>
*trie.c* is the source file for the Trie ADT<br>
*trie.h* specifies the interface to trie.c<br>
*word.c* is the source file for the Word ADT<br>
*word.h* specifies the interface to word.c<br>
*io.c* is the source file for the I/O module<br>
*io.h* specifies the interface to io.c<br>
*endian.h* is the header file for the endianness module<br>
*code.h* is the header file with macros for reserved codes<br>
*Makefile* contains what is needed to clear and recompile<br>
*README.md* describes how to use the program and details parts of it<br>
*DESIGN.pdf* describes the design and process enough to be replicated<br>
*WRITEUP.pdf* includes the necessary analysis of the program<br>

**Resources**<br>
I searched through existing Discord and Piazza questions and discussions in order to debug various parts of my code. I also attended a couple of sections with Omar.