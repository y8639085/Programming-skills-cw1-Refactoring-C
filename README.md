# Documentation of Percolation

## Introduction
The program solves the percolate problem. This is a modified version which includes:
+ Clean up and refactor the source code
+ Allow the user to specify the necessafy values in command line
+ Build script
+ Documentation

### Compilers and versions
Compiler: gcc 4.8.5
Flags:
+ -g(add default debug information to compiled code)
+ -lm('-l' for link, '-m' for math libraries)
+ -lcunit(for cunit test)

## Source files
The source files in folder src includes: arralloc.c arralloc.h percolate.c
percolate.h uni.c uni.h, and a Makefile for compiling and linking all the source files.

## Test files
The cunit test files in folder test includes: cunit_test_driver.c percolate_cunit_test.c percolate_cunit_test.h.
In cunit_test_driver.c, it is the framework of cunit, including initialise and clean-up functions, test suite and test cases.
In percolate_cunit_test.c, there are defination of test cases, including:

+ int suite_init(void)
+ int suite_clean(void;
+ void test_create_map(void)
+ void test_update_map(void)
+ void test_loop_map(void)
+ void test_check_percolate(void)
+ void test_writeDatafile(void)
+ void test_initialize_clusters(void)
+ void test_arrange_clusters(void)

The main function is in "percolate_program.c" and "cunit_test_driver.c".

## Compiling and running
To compile the program part, users need to input "make" in the
command line to invoke "Makefile".
To compile the test part, firstly users need to export three paths, just type following
content to the command line:

+ export C_INCLUDE_PATH=$HOME/include:$C_INCLUDE_PATH
+ export LIBRARY_PATH=$HOME/lib:$LIBRARY_PATH
+ export LD_LIBRARY_PATH=$HOME/lib:$LD_LIBRARY_PATH

This is for set path of CUnit, then input "make test" in the command line.
To clean the mid product such as *.o files, input "make clean" 
to delete all the auto-generated files created during compilation.

After compilation, type "./percoate" to run this program, and
It will require users to specify key variables in this program:
+ The value of map width and height(L)
+ The value of density(rho),
+ The value of seed(seed),
+ Data file name and PGM file name.
+ Maximum number of clusters in PGM file(MAX).

Users should input them in the command line in a specific order.
For example, ./percolate 20 0.4 1564 map.dat map.pgm.

After running your results will be stored in two files, the names are specified by users, the first one is the
initial map generated, the last one is the result map with clusterings after percolating whether it was successful or not.
To open them, you can type "cat FILENAME" in the command line.

## Result
Then this program will run and show you whether it percolates or not.
After that it will generate two files named "map.dat" which shows the map the user created,
and "map.pgm" which shows all the clusters.
