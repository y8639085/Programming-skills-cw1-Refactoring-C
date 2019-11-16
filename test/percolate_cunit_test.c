#include "percolate_cunit_test.h"

int suite_init(void) {
  return 0;
}

int suite_clean(void) {
  return 0;
}

void test_create_map(void) {
  int L = 20;
  int **map = (int**)arralloc(sizeof(int), 2, L+2, L+2);
  float rho = 0.4;




  CU_ASSERT_EQUAL(1, 2);
  //  create_map(L, map, rho);
  //  CU_ASSERT_EQUAL(nEmpty, 230);
}

void test_2(void) {

}

void test_3(void) {

}
