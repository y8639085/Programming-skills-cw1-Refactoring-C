#include <stdio.h>
#include <assert.h>
#include <CUint/Basic.h>
#include "percolate.c"

static int suite_init(void) {
  return 0;
}

static int suite_clean(void) {
  return 0;
}

static test_xx() {

}

int main(int argc, char* argv[]) {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) {
    printf("c test initialize failed\n");
    return CU_get_error();
  }
  /* return registry to case pointer */
  assert(NULL != CU_get_registry());

  /* test if it is running */
  assert(!CU_is_test_running());

  /* add a suite to the registry */
  pSuite = CU_add_suite("suite_xx", suite_init, suite_clean);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test_xx", test_xx))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE)；
  CU_basic_run_tests();

  /* clean up registry and return */
  CU_cleanup_registry();
  return CU_get_error();
}
