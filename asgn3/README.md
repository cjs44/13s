# README Assignment 3
## Caitlin Smith - csmith44 - 2/5/23

In order to run my Assignment 3 program, download the files and start with *make clean* and *make all*. Run *./sorting* with any of the desired command-line options [ahbsqrnpH]. The corresponding tests will be run, and the sorted arrays are printed.<br>

**Command-line Options**<br>
*-a* change the set to run all of the tests<br>
*-h* change the set to run Heap Sort<br>
*-b* change the set to run Batcher Sort<br>
*-s* change the set to run Shell Sort<br>
*-q* change the set to run Quick Sort<br>
*-r* takes an argument and sets it to the seed<br>
*-n* takes an argument and sets it to the array size<br>
*-p* takes an argument and sets it to the print size<br>
*-H* displays a help message of usage and options<br>

**Files**<br>
*batcher.c* contains the implementation of Batcher Sort<br>
*batcher.h* specifies the interface of batcher.c<br>
*shell.c* contains the implementation of Shell Sort<br>
*shell.h* specifies the interface of shell.c<br>
*gaps.h* contains the gap sequence for Shell Sort<br>
*heap.c* contains the implementation of Heap Sort<br>
*heap.h* specifies the interface of heap.c<br>
*quick.c* contains the implementation of Quick Sort<br>
*quick.h* specifies the interface of quick.c<br>
*set.c* contains the implementation of bit-wise Set operations<br>
*set.h* specifies the interface of set.c<br>
*stats.c* contains the implementation of the statistics module<br>
*stats.h* specifies the interface of stats.c<br>
*sorting.c* contains the main() function testing each sort<br>
*Makefile* contains what is needed to format, clear and recompile<br>
*README.md* describes how to run the program and details components of it<br>
*DESIGN.pdf* describes the design and process enough to be replicated<br>
*WRITEUP.pdf* includes the necessary analysis of the program<br>

**Resources**<br>
I attended Dev's section on January 31 and got help understanding each of the sorts more clearly. He explained the process and this helped me code the sorts more easily. I also used the given example script as references for my print statements and outputs.
