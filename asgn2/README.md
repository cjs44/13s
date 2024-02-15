# README Assignment 2
## Caitlin Smith - csmith44 - 1/29/23

In order to run my Assignment 2 program, download the files and start with *make clean* and *make all*. Run *./mathlib-test* with any of the desired command-line options [aebmrvnsh]. The corresponding tests will be run, and the results and comparisons are printed.<br>

**Command-line Options**<br>
*-a* runs all of the tests<br>
*-e* runs the e approximation test<br>
*-b* runs the Bailey-Borwein-Plouffe pi approximation test<br>
*-m* runs the Madhava pi approximation test<br>
*-r* runs the Euler sequence pi approximation test<br>
*-v* runs the Viete pi approximation test<br>
*-n* runs the Newton-Raphson square root approximation test<br>
*-s* enables printing of computed terms statistics<br>
*-h* displays a help message of usage and options<br>

**Files**<br>
*bbp.c* contains the implementation of the BBP formula<br>
*e.c* contains the implementation of the Taylor series for Euler's number<br>
*euler.c* contains the implementation of Euler's solution<br>
*madhava.v* contains the implementation of the Madhava series<br>
*newton.c* contains the implementation of Newton's method<br>
*viete.c* contains the implementation of Viete's formula<br>
*mathlib.h* contains the interface for my math library<br>
*mathlib-test.c* contains the main() function testing each math function<br>
*Makefile* contains what is needed to format, clear and recompile<br>
*README.md* describes how to run the program and details components of it<br>
*DESIGN.pdf* describes the design and process enough to be replicated<br>
*WRITEUP.pdf* includes the necessary analysis of the program<br>

**Resources**<br>
I attended Omar's section on January 25 and got help with creating my Makefile. He explained the components and the basics of it. I also used the given example scripts as references for my print statements and outputs.
