#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arralloc.h"
#include "uni.h"
#include "percolate.h"

// function declarations
void writeDatafile(FILE* fp, int** map, char* datafile, int L);
void writePercfile(FILE* fp, int** map, int L, int MAX, char* percfile);

int main(void) {
    int L;		// map width and height. L >= 1
    int** map;		// two-dimensional array
    float rho;		// density, 0 <= rho <= 1
    int seed;		// for random number generator
    int MAX;		// the number of clusters to output to the PGM file
    char* dataFile;	// data file name
    char* percFile;	// PGM file name

    /* get input from keyboard by user */
    printf("Type in map width and height: \n");
    scanf("%d", &L);

    printf("Type in rho: \n");
    scanf("%f", &rho);

    printf("Type in seed: \n");
    scanf("%d", &seed);

    printf("Type in data file name:(please end with a suffix .dat) \n");
    dataFile = (char*)malloc(sizeof(char) * 100);
    scanf("%s", dataFile);
    printf("Type in PGM file name:(please end with a suffix .pgm) \n");
    percFile = (char*)malloc(sizeof(char) * 100);
    scanf("%s", percFile);

    map = (int**)arralloc(sizeof(int), 2, L + 2, L + 2);

    MAX = L * L;

    rinit(seed);	// generate random number

    printf("Parameters are rho=%f, L=%d, seed=%d\n", rho, L, seed);

    int nfill;        // n squares are not filled into 0
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
    rho, 1.0 - ((double) nfill)/((double) L*L) );

    /* Fix bug. Check all the squares, if 
       is not 0, give the values to them 
       from 1 to n*/
    nfill = 0;
    for (i=1; i<=L; i++) {
        for (j=1; j<=L; j++) {
            if (map[i][j] != 0) {
                nfill++;
                map[i][j] = nfill;
            }
        }
    }

    int loop, nchange, old;
    loop = 1;
    nchange = 1;
    while (nchange > 0) {
        nchange = 0;
        for (i=1; i<=L; i++) {
            for (j=1; j<=L; j++) {
                if (map[i][j] != 0) {
                    old = map[i][j];
                    if (map[i-1][j] > map[i][j]) map[i][j] = map[i-1][j];
                        if (map[i+1][j] > map[i][j]) map[i][j] = map[i+1][j];
                            if (map[i][j-1] > map[i][j]) map[i][j] = map[i][j-1];
                                if (map[i][j+1] > map[i][j]) map[i][j] = map[i][j+1];
                                    if (map[i][j] != old) {
                                        nchange++;
                                    }
                }
            }
        }
        printf("Number of changes on loop %d is %d\n", loop, nchange);
        loop++;
    }

    for (j=L; j>=1; j--) {
        for (i=1;i<=L; i++) {
            map[i][j] = (map[i][j]*1)+0;
        }
    }

    int itop, ibot, percClusterNum;
    int percs = 0;
    percClusterNum = 0;
    for (itop=1; itop<=L; itop++) {
        if (map[itop][L] > 0) {
            for (ibot=1; ibot<=L; ibot++) {
                if (map[itop][L] == map[ibot][1]) {
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

    FILE* fp;

    writeDatafile(fp, map, dataFile, L);
    writePercfile(fp, map, L, MAX, percFile);
}

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

void writePercfile(FILE* fp, int** map, int L, int MAX, char* percFile) {
    int nCluster, maxSize;
    struct cluster *clustList;
    int colour;
    int *rank;
    int i, j;
    clustList = (struct cluster*)arralloc(sizeof(struct cluster), 1, L*L);
    rank = (int*)arralloc(sizeof(int), 1, L*L);
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
    percsort(clustList, L*L);
    maxSize = clustList[0].size;
    for (nCluster=0; nCluster < L*L && clustList[nCluster].size > 0; nCluster++);   // ？？？？？？？
    if (MAX > nCluster) {
        MAX = nCluster;
    }
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
    fprintf(fp, "P2\n");
    if (MAX > 0)
        fprintf(fp, "%d %d\n%d\n", L, L, MAX);
    else
        fprintf(fp, "%d %d\n%d\n", L, L, 1);
    for (j=L; j>=1; j--) {
        for (i=1;i<=L; i++) {
            colour = map[i][j];
            if (map[i][j] > 0) {
                colour = rank[map[i][j]-1];
                if (colour >= MAX)
                    colour = MAX;
            }
            else
                colour = MAX;
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

void percsort(struct cluster *list, int n) {
    qsort(list, (size_t) n, sizeof(struct cluster), clustCompare);
}


