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
 * Test
 */
void test_create_map(void);

/*
 * Test
 */
void test_update_map(void);

/*
 * Test
 */
void test_loop_map(void);

void test_check_percolate(void);

void test_writeDatafile(void);

void test_initialize_clusters(void);

void test_arrange_clusters(void);
#endif
