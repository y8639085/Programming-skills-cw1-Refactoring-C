#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arralloc.h"
#include "percolate.h"

int main(int argc, char* argv[]) {
    int L;		// map width and height. L >= 1
    int** map;		// two-dimensional array
    float rho;		// density, 0 <= rho <= 1
    int seed;		// for random number generator
    int MAX;		// the number of clusters to output to the PGM file
    char* dataFile; 	// data file name
    char* percFile;	// PGM file name
    FILE* fp;

    // inspect command line arguments
    if (argc != 7) {
        printf("Please input all arguments correctly!\n");
        exit(1);
    }

    int len = strlen(argv[1]);
    int i, j = 0;
    for (i = 0; i < len; i++) {
        if(argv[1][i] <= 57 && argv[1][i] >= 48)
            j++;
    }
    if (j != len) {
        printf("Please input an integer for length!\n");
        exit(1);
    }

    if (argv[2][0] != 48 || argv[2][1] != 46) {
        printf("Please input a float number between 0 and 1 for rho!\n");
        exit(1);
    }
    j = 0;
    len = strlen(argv[2]);
    for (i = 2; i < len; i++) {
        if (argv[2][i] <= 57 && argv[2][i] >= 48)
	    j++;
    }
    if (j != len - 2) {
        printf("Please input a float number between 0 and 1 for rho!\n");
	exit(1);
    }

    j = 0;
    len = strlen(argv[3]);
    for (i = 0; i < len; i++) {
        if (argv[3][i] <= 57 && argv[3][i] >= 48)
	    j++;
    }
    if (j != len) {
        printf("Please input an integer for seed!\n");
        exit(1);
    }

    j = 0;
    len = strlen(argv[6]);
    for (i = 0; i < len; i++) {
        if (argv[6][i] <= 57 && argv[6][i] >= 48)
	  j++;
    }
    if (j != len) {
        printf("Please input an integer for MAX\n");
        exit(1);
    }

    L = atoi(argv[1]);
    rho = atof(argv[2]);
    seed = atoi(argv[3]);
    dataFile = argv[4];
    percFile = argv[5];
    MAX = atoi(argv[6]);

    map = (int**)arralloc(sizeof(int), 2, L + 2, L + 2); // add halo to the map

    rinit(seed);	// generate random number

    printf("Parameters are rho=%f, L=%d, seed=%d\n", rho, L, seed);
    solve_percolate(L, map, rho);

    writeDatafile(L, map, dataFile, fp);
    writePercfile(L, MAX, map, percFile, fp);
}
