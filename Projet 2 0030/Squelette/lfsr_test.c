#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include "seatest.h"
#include "pnm.h"
#include "lsfr.h"

static void test_operation()
{
   LSFR *mylsfr = initialisation("01101000010", 8);

   assert_int_equal(operation(mylsfr), 1); 

  destructor(mylsfr);
}



static void test_fixture()
{
   test_fixture_start();
   run_test(test_operation);
   
   test_fixture_end();
} //fin test_fixture()

static void all_tests()
{
   test_fixture();
} //fin  all_tests()

int main()
{
   return run_tests(all_tests);
} //fin main()