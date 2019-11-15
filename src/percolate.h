#ifndef PERCOLATE_H
#define PERCOLATE_H

struct cluster
{
  int id;
  int size;
};

void percsort(struct cluster *list, int n);

#endif
