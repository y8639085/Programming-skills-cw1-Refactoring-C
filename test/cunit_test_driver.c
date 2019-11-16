#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "percolate_cunit_test.h"

int main() {

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
  pSuite = CU_add_suite("suite_percolate", suite_init, suite_clean);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test_create_map", test_create_map)) ||
      (NULL == CU_add_test(pSuite, "test_2", test_2)) ||
      (NULL == CU_add_test(pSuite, "test_3", test_3))) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* run all tests using the CUnit Basic interface which 
     outputs results to command-line */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();

  /*
   * Run all tests using CUnit Automated interface which outputs
   * resuls to a file, default name CUnitAutomated-Results.xml.
   * DTD CUnit-Run.dtd and XSL stylesheet CUnit-Run.xsl in share/
   * Uncomment this line to override default output file prefix.
   * CU_set_output_filename("Test");
   */
  CU_list_tests_to_file();

  /*
   * Output listing of tests in suites to a file, default name
   * CUnitAutomated-Listing.xml
   * DTD Cunit-List.dtd and XSL stylesheet CUnit-List.xsl in share/
   */
  CU_automated_run_tests();

  /* clean up registry and return */
  CU_cleanup_registry();
  return CU_get_error();
}
