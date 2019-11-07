# Documentation of Percolation

## The program solves the percolate problem.

The source files includes: arralloc.c arralloc.h percolate.c
percolate.h uni.c uni.h, and a Makefile for compiling and linking all the source files.

The main logic is in "percolate.c".

To compile and run it, users need to input "make" in the
command line to invoke "Makefile", then input "make clean" 
to delete all the auto-generated files created during compilation.

After compilation, type "./percoate" to run this program, and
It will require users to specify key variables in this program:
(e.g. the value of map width and height(L), the value of density(rho),
the value of seed(seed), data file name and PGM file name.)
Users should input them in the command line in a specific order.
For example, ./percolate 20 0.4 1564 map.dat map.pgm

Then this program will run and show you whether it percolates or not.
After that it will generate two files named "map.dat" which shows the map the user created,
and "map.pgm" which shows all the clusters.
