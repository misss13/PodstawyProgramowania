#include "CUnit/Basic.h"
#include "fyszr.c"

//----------Testy-------------
void fyszr_testy()
{
  int d=0;
  char slowo[100];

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

  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("fyszr_testy_suite", 0, 0);

  if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  if (NULL == CU_add_test(pSuite, "fyszr_testy", fyszr_testy))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  CU_basic_set_mode(CU_BRM_VERBOSE);

  CU_basic_run_tests();
  return CU_get_error();
}
