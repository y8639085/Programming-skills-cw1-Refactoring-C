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
  int **map;
  map =  (int**)arralloc(sizeof(int), 2, L+2, L+2);
  float rho = 0.4;

  create_map(L, map, rho);
  printf("1111\n");
  CU_ASSERT_EQUAL(map[0][0], 1);
}

void test_2(void) {

}

void test_3(void) {

}
