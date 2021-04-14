#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 100
#include "CUnit/Basic.h"
#include "zadanie3.2.c"

void test_ascii()
{
  //1
  char *sze = getHexAscii('(');
  CU_ASSERT_STRING_EQUAL(sze , "28");
  free(sze);
  //2
  sze = getHexAscii('Z');
  CU_ASSERT_STRING_EQUAL(sze , "5a");
  free(sze);
  //3
  sze = getHexAscii('z');
  CU_ASSERT_STRING_EQUAL(sze , "7a");
  free(sze);
}

void test_compress()
{
  char **slowo=(char **)malloc(3*sizeof(char*));
  char *com;
  FOR(i,3)
  {
    slowo[i]=(char*)malloc(duzo*sizeof(char));
    *slowo[i]='\0';
  }
  //1
  strcpy(slowo[0], "aaaa bbbbbbbbb\n");
  strcpy(slowo[1], "     ((((((((((((%)");
  com=compress(slowo, 2);
  CU_ASSERT_STRING_EQUAL(com, "aaaa b(9)\n (5)%28(12)%25(1)%29(1)");
  free(com);

  //2
  strcpy(slowo[0], "aaaaaaaaaaaaaa bbbbbbb (((((((%%%%)))))))\n");
  com=compress(slowo, 1);
  CU_ASSERT_STRING_EQUAL(com, "a(14) b(7) %28(7)%25(4)%29(7)\n");
  free(com);
  FOR(i,3)
    free(slowo[i]);
  free(slowo);
}

void test_decompress()
{
  char **slowo=(char **)malloc(3*sizeof(char*));
  char *dec;
  FOR(i,3)
    {
      slowo[i]=(char*)malloc(duzo*sizeof(char));
      *slowo[i]='\0';
    }
  //1
  strcpy(slowo[0], "aaaa b(9)\n");
  strcpy(slowo[1], " (5)%28(12) %25(1)%29(1)\n");
  dec=decompress(slowo, 2);
  CU_ASSERT_STRING_EQUAL(dec, "aaaa bbbbbbbbb\n     (((((((((((( %)\n");
  free(dec);
  //2
  strcpy(slowo[0], "a(15)\n");
  strcpy(slowo[1], " b(16)\n");
  strcpy(slowo[2], "  c(14)\n");
  dec=decompress(slowo, 3);
  CU_ASSERT_STRING_EQUAL(dec, "aaaaaaaaaaaaaaa\n bbbbbbbbbbbbbbbb\n  cccccccccccccc\n");

  free(dec);
  FOR(i,3)
    free(slowo[i]);
  free(slowo);
}

int main() {
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("test_trzecie", 0, 0);

	if (NULL == pSuite)
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

	if (NULL == CU_add_test(pSuite, "test_ascii", test_ascii))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

	if (NULL == CU_add_test(pSuite, "test_compress", test_compress))
    {
      CU_cleanup_registry();
      return CU_get_error();
    }

  	if (NULL == CU_add_test(pSuite, "test_decompress", test_decompress))
    {
    CU_cleanup_registry();
    return CU_get_error();
    }

	CU_basic_set_mode(CU_BRM_VERBOSE);

	CU_basic_run_tests();
	return CU_get_error();
}
