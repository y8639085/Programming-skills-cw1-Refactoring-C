# Documentation of Percolation

## Introduction
The program solves the percolate problem. This is a modified version which includes:
+ Clean up and refactor the source code
+ Allow the user to specify the necessafy values in command line
+ Build script
+ Documentation

### Compilers and versions
Compiler: gcc 4.8.5
Flags: -g(add default debug information to compiled code)
       -lm ('-l' for link, '-m' for math libraries)

## Source files
The source files includes: arralloc.c arralloc.h percolate.c
percolate.h uni.c uni.h, and a Makefile for compiling and linking all the source files.

The main logic is in "percolate.c".

## Compiling and running
To compile and run it, users need to input "make" in the
command line to invoke "Makefile", then input "make clean" 
to delete all the auto-generated files created during compilation.

After compilation, type "./percoate" to run this program, and
It will require users to specify key variables in this program:
+ The value of map width and height(L)
+ The value of density(rho),
+ The value of seed(seed),
+ Data file name and PGM file name.
+ Maximum number of clusters in PGM file(MAX)
Users should input them in the command line in a specific order.
For example, ./percolate 20 0.4 1564 map.dat map.pgm

After that your results will be stored in two files named "map.dat" and "map.pgm", the first one is the
initial map generated, the last one is the result map with clusterings after percolating whether it was successful or not.
To open them, you can type "cat FILENAME" in the command line.

## Result
Then this program will run and show you whether it percolates or not.
After that it will generate two files named "map.dat" which shows the map the user created,
and "map.pgm" which shows all the clusters.
