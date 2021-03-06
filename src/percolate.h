#ifndef PERCOLATE_H
#define PERCOLATE_H

struct cluster
{
  int id;
  int size;
};

void solve_percolate(int L, int** map, float rho);
void create_map(int L, int** map);
void initialize_map(int L, int** map, float rho);
void update_map(int L, int** map);
void loop_map(int L, int** map);
int check_percolate(int L, int** map);
void writeDatafile(int L, int** map, char* dataFile, FILE* fp);
void writePercfile(int L, int MAX, int** map, char* percFile, FILE* fp);
void initialize_clusters(int L, int** map, struct cluster* clustList, int* rank);
void arrange_clusters(int L, int** map, int nCluster, int maxSize, int MAX, struct cluster* clustList, int* rank, char* percFile, FILE* fp);
void percsort(struct cluster *list, int n);

#endif
