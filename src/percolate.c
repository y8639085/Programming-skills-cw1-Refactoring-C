#include <stdio.h>
#include <stdlib.h>
#include "arralloc.h"
#include "uni.h"
#include "percolate.h"

/**
 * This function contains the main logic
 * First initialize each empty square with a unique positive integer
 * Then loop over all squares many times and during each loop we replace each
 * square with the maximum of its four neighbours.
 *
 * nEmpty: n squares which are specified an integer
 * r: a ramdom number compared with rho, if r > rho, value the square with 1
 * loop: number of loops
 * change: the number of values which were changed in last round
 **/
void solve_percolate(int L, int** map, float rho) {
    // create and initialize the map
    create_map(L, map, rho);

    /* Loop over all the squares in the grid many times and replace each 
       square with the maximum of its four neighbours. */
    loop_map(L, map);

    check_percolate(L, map);
}

void create_map(int L, int** map, float rho) {
    int nEmpty;
    int i, j;
    float r;
    for (i=0; i<L+2; i++) {      // initialise all the squares to be 0(gray)
        for (j=0; j<L+2; j++) {
	    map[i][j] = 0;
        }
    }
    nEmpty = 0;
    for (i=1; i<=L; i++) {
        for (j=1; j<=L; j++) {
	    r=random_uniform();
	    if(r > rho) {
	        nEmpty++;
                map[i][j]=1;
	    }
	}
    }

    printf("rho = %f, actual density = %f\n",
    rho, 1.0 - ((double) nEmpty)/((double) L*L) );    // show the density of 0

    nEmpty = 0;
    for (i=1; i<=L; i++) {
        for (j=1; j<=L; j++) {
            if (map[i][j] != 0) {
	        nEmpty++;
	        map[i][j] = nEmpty;
            }
	}
    }
}

void loop_map(int L, int** map) {
    int loop, nchange, old, i, j;
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
}

void check_percolate(int L, int** map) {
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
void writeDatafile(int L, int** map, char* dataFile, FILE* fp) {
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
void writePercfile(int L, int MAX, int** map, char* percFile, FILE* fp) {
    int nCluster, maxSize;
    struct cluster *clustList;
    int *rank;

    // define all clusters as structs
    clustList = (struct cluster*)arralloc(sizeof(struct cluster), 1, L*L);
    rank = (int*)arralloc(sizeof(int), 1, L*L);

    // initialize structs
    initialize_clusters(L, map, clustList, rank);

    // sort all the clusters from large to small
    percsort(clustList, L*L);
    maxSize = clustList[0].size;
    // find all the clusters whose size is not 0
    for (nCluster=0; nCluster < L*L && clustList[nCluster].size > 0; nCluster++);
    if (MAX > nCluster) {
        MAX = nCluster;
    }

    arrange_clusters(L, map, nCluster, maxSize, MAX, clustList, rank, percFile, fp);
    //    cluster_colour(L, MAX, map, rank, fp);

    printf("...done\n");
    //    fclose(fp);
    printf("File closed\n");
    free(clustList);
    free(rank);

    free(map);
}

void initialize_clusters(int L, int** map, struct cluster* clustList, int* rank) {
    int i, j;
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
}

void arrange_clusters(int L, int** map, int nCluster, int maxSize, int MAX,  struct cluster* clustList, int* rank, char* percFile, FILE* fp) {
    int i, j;
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
    /*}

      void cluster_colour(int L, int MAX, int** map, int* rank, FILE* fp) {*/
    /* the colour values range from 0 to the number of clusters inclusive */
    //    int i, j;
    int colour;
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
    fclose(fp);
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

/**
 * Compare two clusters using buint-in function in c library
 *
 * list: pointer of the first item
 * n: number of the items
 * clustCompare: callback funtion 
**/
void percsort(struct cluster *list, int n) {
    qsort(list, (size_t) n, sizeof(struct cluster), clustCompare);
}
