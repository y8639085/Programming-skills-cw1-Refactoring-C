#ifndef PERCOLATE_CUNIT_TEST_H
#define PERCOLATE_CUNIT_TEST_H

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "percolate.h"

/*
 * Initialize test suite.
 * @return zero on success, non-zero otherwise.
 */
int suite_init(void);

/*
 * Clean up test suite.
 * @return zero on success, non-zero othrewise.
 */
int suite_clean(void);

/*
 * Test if this function could create a map with all
 * squares are 0.
 */
void test_create_map(void);

/*
 * Test if this function could assign a unique value
 * to each non-zero square.
 */
void test_update_map(void);

/*
 * Test if this function could change the center value
 * to the largest one surroud it by loop.
 */
void test_loop_map(void);

/*
 * Test if this function could check a percolation
 * correctly
 */
void test_check_percolate(void);

/*
 * Test if this function could write data to data file
 * correctly
 */
void test_writeDatafile(void);

/*
 * Test if this function could create and initialise
 * the clusters correctly.
 */
void test_initialize_clusters(void);

/*
 * Test if this function could sort the clusters and
 * assign the colours correctly.
 */
void test_arrange_clusters(void);
#endif
