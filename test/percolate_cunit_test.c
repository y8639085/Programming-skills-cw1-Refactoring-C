#include "percolate_cunit_test.h"
#include "arralloc.h"
#include "uni.h"

int suite_init(void) {
  return 0;
}

int suite_clean(void) {
  return 0;
}

void test_create_map(void) {
  int L = 20;
  int **map = (int**)arralloc(sizeof(int), 2, L+2, L+2);

  create_map(L, map);

  CU_ASSERT_EQUAL(map[0][0], 0);
  CU_ASSERT_EQUAL(map[1][1], 0);
  CU_ASSERT_EQUAL(map[5][3], 0);
  CU_ASSERT_EQUAL(map[14][16], 0);
  CU_ASSERT_EQUAL(map[21][21], 0);
}

void test_update_map(void) {
  int L = 20;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);

  int i, j;
  for (i=0; i<L+2;i++) {
    for (j=0; j<L+2;j++) {
      map[i][j]=0;
    }
  }

  for (i=1; i<=L; i++) {
    for (j=1; j<=L; j++) {
	map[i][j] = 1;
    }
  }

  update_map(L, map);

  CU_ASSERT_EQUAL(map[4][5], 65);
  CU_ASSERT_EQUAL(map[11][13], 213);
  CU_ASSERT_EQUAL(map[21][21], 0);
  CU_ASSERT_EQUAL(map[1][1], 1);
  CU_ASSERT_EQUAL(map[0][0], 0);
}

void test_loop_map(void) {
  int L = 20;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);

  int i, j;
  create_map(L, map);

  for (i=1; i<=L; i++) {
    for (j=1; j<=L; j++) {
	map[i][j] = 1;
    }
  }
  update_map(L, map);

  loop_map(L, map);

  CU_ASSERT_EQUAL(map[4][5], 400);
  CU_ASSERT_EQUAL(map[11][13], 400);
  CU_ASSERT_EQUAL(map[21][21], 0);
  CU_ASSERT_EQUAL(map[1][1], 400);
  CU_ASSERT_EQUAL(map[0][0], 0);
}

void test_check_percolate(void) {
  int L = 20;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);

  int i, j;
  create_map(L, map);

  for(i=1; i<=L; i++) {
    map[1][i]=1;
  }

  CU_ASSERT_EQUAL(check_percolate(L, map), 1);
}

void test_writeDatafile(void) {
  int L = 10;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);
  char* dataFile = "testlog.dat";
  FILE* fp;
  fp = fopen(dataFile, "w");

  create_map(L, map);
  int i, j;
  for (i=1; i<=L; i++) {
    for (j=1; j<=L; j++) {
	map[i][j] = 1;
    }
  }

  update_map(L, map);

  writeDatafile(L, map, dataFile, fp);

  fp = fopen(dataFile, "r");
  char strLine[1024], strLine2[1024];
  fgets(strLine, 1024, fp);
  fgets(strLine2, 1024, fp);

  CU_ASSERT_EQUAL(strcmp(strLine, "   10   20   30   40   50   60   70   80   90  100\n"), 0);
  CU_ASSERT_EQUAL(strcmp(strLine2, "    9   19   29   39   49   59   69   79   89   99\n"), 0);
}

void test_initialize_clusters(void) {
  int L = 20;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);
  struct cluster *clustList = (struct cluster*)arralloc(sizeof(struct cluster), 1, L*L);
  int* rank = (int*)arralloc(sizeof(int), 1, L*L);
  int i, j;
  create_map(L, map);
  for (i=1; i<=L; i++) {
    for (j=1; j<=L; j++) {
	map[i][j] = 1;
    }
  }
  update_map(L, map);

  initialize_clusters(L, map, clustList, rank);

  CU_ASSERT_EQUAL(clustList[map[1][1]-1].size, 1);
  CU_ASSERT_EQUAL(clustList[map[0][0]-1].size, 0);
  CU_ASSERT_EQUAL(clustList[map[18][13]-1].size, 1);
}

void test_arrange_clusters(void) {
  int L = 20;
  int nCluster, maxSize;
  int** map = (int**)arralloc(sizeof(int), 2, L+2, L+2);
  struct cluster *clustList = (struct cluster*)arralloc(sizeof(struct cluster), 1, L*L);
  int* rank = (int*)arralloc(sizeof(int), 1, L*L);
  char* percFile = "testlog.pgm";;
  FILE* fp;
  int i, j;
  create_map(L, map);
  for(i=1; i<=L; i++) {
    map[1][i]=1;
  }
  for(i=1; i<=L; i++) {
    map[4][i]=4;
  }
  for(i=1; i<=L; i++) {
    map[7][i]=7;
  }
  map[2][1]=1;
  map[5][1]=4;
  map[5][2]=4;
  map[5][3]=4;
  map[8][1]=7;
  map[8][2]=7;
  /*    for (i=0;i<L+2;i++) {
    for (j=0;j<L+2;j++) {
      printf(" %d ", map[i][j]);
      if(j==21) {
	printf("\n");
      }
    }
    }*/

  initialize_clusters(L, map, clustList, rank);
  percsort(clustList, L*L);
  maxSize = clustList[0].size;

  CU_ASSERT_EQUAL(maxSize, 23);
  CU_ASSERT_EQUAL(clustList[1].size, 22);
  CU_ASSERT_EQUAL(clustList[2].size, 21);

  for (nCluster=0; nCluster < L*L && clustList[nCluster].size > 0; nCluster++);
  CU_ASSERT_EQUAL(nCluster, 3);

  arrange_clusters(L, map, nCluster, maxSize, 3, clustList, rank, percFile, fp);
  /*  fp = fopen("testlog.pgm", "r");
  char strLine[1024];
  fgets(strLine, 1024, fp);
  fgets(strLine, 1024, fp);
  fgets(strLine, 1024, fp);

  char b;
  for (i=0; i<18; i++) {
    b = fgetc(fp);
    printf("%s", &b);
  }

  char a = fgetc(fp);
  printf("\nthe char is %s\n", &a);
  CU_ASSERT_EQUAL();*/
}
