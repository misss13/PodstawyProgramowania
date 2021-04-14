#include "CUnit/Basic.h"
#include "fyszr.c"

//----------Testy-------------
void fyszr_testy()
{
  int d=0;
  char slowo[53];

	strcpy(slowo, "to be or not to be");
  d = strlen(slowo);
  FyszrCezara(slowo, d);
  CU_ASSERT_STRING_EQUAL(slowo, "vq dg qt pqv vq dg");

  strcpy(slowo, "ala ma kota");
  d = strlen(slowo);
  FyszrCezara(slowo, d);
  CU_ASSERT_STRING_EQUAL(slowo, "dod pd nrwd");

  strcpy(slowo, "abcdefghijklmnopqrstuvwxyz");
  d = strlen(slowo);
  FyszrCezara(slowo, d);
  CU_ASSERT_STRING_EQUAL(slowo, "abcdefghijklmnopqrstuvwxyz");

  strcpy(slowo, " a b c d e f g h i j k l m n o p q r s t u v w x y z");
  d = strlen(slowo);
  FyszrCezara(slowo, d);
  CU_ASSERT_STRING_EQUAL(slowo, " b c d e f g h i j k l m n o p q r s t u v w x y z a");
}

int main()
{
  CU_pSuite pSuite = NULL;

  // Initialize the CUnit test registry
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  // Add a suite to the registry
  pSuite = CU_add_suite("fyszr_testy_suite", 0, 0);

  // Always check if add was successful
  if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Add the test to the suite
  if (NULL == CU_add_test(pSuite, "fyszr_testy", fyszr_testy))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  // Sets the basic run mode, CU_BRM_VERBOSE will show maximum output of run details
  // Other choices are: CU_BRM_SILENT and CU_BRM_NORMAL
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // Run the tests and show the run summary
  CU_basic_run_tests();
  return CU_get_error();
}
