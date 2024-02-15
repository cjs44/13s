# README Assignment 4
## Caitlin Smith - csmith44 - 2/12/23

In order to run my Assignment 4 program, download the files and start with *make clean* and *make all*. Run *./life* with any of the desired command-line options [tsn:i:o:h]. The Game of Life program will run and the result will be printed to the outfile.<br>

**Command-line Options**<br>
*-t* sets the Universe to be toroidal<br>
*-s* will silence the ncurses display<br>
*-n* specifies the number of generations (default: 100)<br>
*-i* specifies the infile (default: stdin)<br>
*-o* specifies the outfile (default: stdout)<br>
*-h* displays a help message of usage and options<br>

**Files**<br>
*universe.c* contains the implementation of the Universe ADT<br>
*universe.h* specifies the interface of universe.c<br>
*life.c* contains main() and the implementation of the Game of Life<br>
*Makefile* contains what is needed to format, clear and recompile<br>
*README.md* describes how to run the program and details components of it<br>
*DESIGN.pdf* describes the design and process enough to be replicated<br>
*WRITEUP.pdf* includes the necessary analysis of the program<br>

**Resources**<br>
I attended Omar's section on February 8 and got help understanding the universe.c functions more clearly. He explained memory allocation and ncurses a bit as well. I also used the given example script as reference for the printing.
