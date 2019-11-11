#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arralloc.h"
#include "uni.h"
#include "percolate.h"

// function declarations
void writeDatafile(FILE* fp, int** map, char* datafile, int L);
void writePercfile(FILE* fp, int** map, int L, int MAX, char* percfile);
void percolate(int L, int** map, float rho);

int main(int argc, char* argv[]) {
    int L;		// map width and height. L >= 1
    int** map;		// two-dimensional array
    float rho;		// density, 0 <= rho <= 1
    int seed;		// for random number generator
    int MAX;		// the number of clusters to output to the PGM file
    char* dataFile;	// data file name
    char* percFile;	// PGM file name

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

    map = (int**)arralloc(sizeof(int), 2, L + 2, L + 2);

    MAX = atoi(argv[6]);

    rinit(seed);	// generate random number

    printf("Parameters are rho=%f, L=%d, seed=%d\n", rho, L, seed);
    percolate(L, map, rho);

    FILE* fp;

    writeDatafile(fp, map, dataFile, L);
    writePercfile(fp, map, L, MAX, percFile);

}

void percolate(int L, int** map, float rho) {
    int nfill;        // n squares which are filled into 1
    int i, j;
    float r;
    for (i=0; i<L+2; i++) {      // initialise all the squares to be 0(gray)
        for (j=0; j<L+2; j++) {
	    map[i][j] = 0;
        }
    }
    nfill = 0;
    for (i=1; i<=L; i++) {
        for (j=1; j<=L; j++) {
	    r=random_uniform();    // generate a random number, if r > rho then let the square be filled.
	        if(r > rho) {
                    nfill++;
                    map[i][j]=1;
	        }
	}
    }

    printf("rho = %f, actual density = %f\n",
    rho, 1.0 - ((double) nfill)/((double) L*L) );    // show the density of 0

    /* Fix bug. Check all the squares, if 
       is not 0, give the values to them 
       from 1 to n */
    nfill = 0;
    for (i=1; i<=L; i++) {
        for (j=1; j<=L; j++) {
            if (map[i][j] != 0) {
	        nfill++;
	        map[i][j] = nfill;
            }
	}
    }
    /* Loop over all the squares in the grid many times and replace each 
       square with the maximum of its four neighbours. */
    int loop, nchange, old;
    loop = 1;
    nchange = 1;
    while (nchange > 0) {
        nchange = 0;
	for (i=1; i<=L; i++) {
            for (j=1; j<=L; j++) {
	        if (map[i][j] != 0) {
		    old = map[i][j];
		    /* check all four neighbours and compare */
		    if (map[i-1][j] > map[i][j]) map[i][j] = map[i-1][j]; 
		        if (map[i+1][j] > map[i][j]) map[i][j] = map[i+1][j];
		            if (map[i][j-1] > map[i][j]) map[i][j] = map[i][j-1];
			        if (map[i][j+1] > map[i][j]) map[i][j] = map[i][j+1];
			            if (map[i][j] != old) nchange++;
                                    
	            }
		}
	    }
	printf("Number of changes on loop %d is %d\n", loop, nchange);
	loop++;
    }

    /*    for (j=L; j>=1; j--) {//????????????????
        for (i=1;i<=L; i++) {
            map[i][j] = (map[i][j]*1)+0;
	}
	}*/

    /* check if there is a cluster percolates */
    int itop, ibot, percClusterNum;
    int percs = 0;
    percClusterNum = 0;
    for (itop=1; itop<=L; itop++) {
        if (map[itop][L] > 0) {
            for (ibot=1; ibot<=L; ibot++) {
	        if (map[itop][L] == map[ibot][1]) {    // check if they share a same number
	    	    percs = 1;
		    percClusterNum = map[itop][L];
		}
            }
	}
    }
    if (percs)
        printf("Cluster DOES percolate. Cluster number: %d\n", percClusterNum);
    else
	printf("Cluster DOES NOT percolate\n");
}

/* write the map into the data file */
void writeDatafile(FILE* fp, int** map, char* dataFile, int L) {
    int i, j;
    printf("Opening file <%s>\n", dataFile);
    fp = fopen(dataFile, "w");
    printf("Writing data ...\n");
    for (j = L; j >= 1; j--) {
        for (i = 1; i <= L; i++) {
            fprintf(fp, " %4d", map[i][j]);
        }
        fprintf(fp, "\n");
    }
    printf("...done\n");
    fclose(fp);
    printf("File closed\n");
}

/* write data into the PGM file */
void writePercfile(FILE* fp, int** map, int L, int MAX, char* percFile) {
    int nCluster, maxSize;
    struct cluster *clustList;
    int colour;
    int *rank;
    int i, j;
    // define all clusters as structs
    clustList = (struct cluster*)arralloc(sizeof(struct cluster), 1, L*L);
    rank = (int*)arralloc(sizeof(int), 1, L*L);
    // initialize structs
    for (i=0; i < L*L; i++) {
        rank[i] = -1;
        clustList[i].size = 0;
        clustList[i].id   = i+1;
    }
    for (i=1;i<=L; i++) {
        for (j=1; j<=L; j++) {
            if (map[i][j] != 0) {
                ++(clustList[map[i][j]-1].size);
            }
        }
    }
    // sort all the clusters from large to small
    percsort(clustList, L*L);
    maxSize = clustList[0].size;
    // find all the clusters whose size is not 0
    for (nCluster=0; nCluster < L*L && clustList[nCluster].size > 0; nCluster++);
    if (MAX > nCluster) {
        MAX = nCluster;
    }
    // arrange clusters from large to small
    for (i=0; i < nCluster; i++) {
        rank[clustList[i].id - 1] = i;
    }
    printf("Opening file <%s>\n", percFile);
    fp = fopen(percFile, "w");
    printf("Map has %d clusters, maximum cluster size is %d\n",
    nCluster, maxSize);
    if (MAX == 1)
        printf("Displaying the largest cluster\n");
    else if (MAX == nCluster)
        printf("Displaying all clusters\n");
    else
        printf("Displaying the largest %d clusters\n", MAX);

    printf("Writing data ...\n");
    fprintf(fp, "P2\n");    // states that this is a PGM file
    if (MAX > 0)
        fprintf(fp, "%d %d\n%d\n", L, L, MAX); 
    else
        fprintf(fp, "%d %d\n%d\n", L, L, 1);
    /* the colour values range from 0 to the number of clusters inclusive */ 
    for (j=L; j>=1; j--) {
        for (i=1;i<=L; i++) {
	  // colour = map[i][j];
            if (map[i][j] > 0) {
                colour = rank[map[i][j]-1];
                if (colour >= MAX)
                    colour = MAX;
            }
            else
                colour = MAX;
            // maximum colour value
            fprintf(fp, " %4d", colour);
        }
        fprintf(fp,"\n");
    }
    printf("...done\n");
    fclose(fp);
    printf("File closed\n");
    free(clustList);
    free(rank);

    free(map);
}
/* compare two items */
static int clustCompare(const void *p1, const void *p2) {
    int size1, size2, id1, id2;

    size1 = ((struct cluster *) p1)->size;
    size2 = ((struct cluster *) p2)->size;

    id1   = ((struct cluster *) p1)->id;
    id2   = ((struct cluster *) p2)->id;

    if (size1 != size2)
        return(size2 - size1);
    else
        return(id2 - id1);
}

/* compare two clusters using buint-in function in c library
   list: pointer of the first item
   n: number of the items
   clustCompare: callback funtion */
void percsort(struct cluster *list, int n) {
    qsort(list, (size_t) n, sizeof(struct cluster), clustCompare);
}
