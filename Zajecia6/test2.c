#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

typedef struct{
  int hour;
  int minute;
  int duration;
} Term;

Term **term;

void Term__init(Term* term, int hour, int minute, int duration){
  term->hour=hour;
  term->minute=minute;
  term->duration=duration;
}

Term* Term__create(int hour, int minute, int duration){
  Term *create=malloc(sizeof(Term));
  Term__init(create, hour, minute, duration);
}

void Term__destroy(Term* term){
  free(term);
}

char* Term__toString(Term* term){
  char *str=malloc(20*sizeof(char));
  snprintf(str, sizeof(str)*5, "%d:%d [%d]", term->hour, term->minute, term->duration);
  return str;
}

bool Term__earlierThan(Term* term1, Term *term2){ //nie istnieja w c to inty
  if(term1->hour < term2->hour)
    return true;
  else if(term1->hour == term2->hour && term1->minute < term2->minute)
    return true;
  else
    return false;
}

bool Term__laterThan(Term* term1, Term *term2){
  if(term1->hour > term2->hour)
    return true;
  else if(term1->hour == term2->hour && term1->minute > term2->minute)
    return true;
  else
    return false;
}

bool Term__equals(Term* term1, Term *term2){
  if(term1->hour == term2->hour && term1->minute == term2->minute && term1->duration == term2->duration)
    return true;
  else
    return false;
}

Term* Term__endTerm(Term* term1, Term *term2){
  int duration = (term2->hour - term1->hour)*60;
  duration += term2->minute - term1->minute;
  Term *term=Term__create(term1->hour, term1->minute, duration > 0 ? duration : 0);
  return term;
}

//--------------------------------testy--------------------------------------------
void test_init(){
  Term terms[3];
  Term__init(&terms[0], 19, 45, 90);
  Term__init(&terms[1], 10, 15, 60);
  Term__init(&terms[2], 19, 30, 15);
  CU_ASSERT_EQUAL(terms[0].hour, 19);
  CU_ASSERT_EQUAL(terms[1].minute, 15);
  CU_ASSERT_EQUAL(terms[2].duration, 15);
}

void test_create(){
  term = malloc(3 * sizeof(*term));
  term[0]=Term__create(19, 30, 90);
  term[1]=Term__create(10, 15, 120);
  term[2]=Term__create(19, 45, 45);
  CU_ASSERT_EQUAL(term[0]->hour, 19);
  CU_ASSERT_EQUAL(term[1]->minute, 15);
  CU_ASSERT_EQUAL(term[2]->duration, 45);
}

void test_string(){
  CU_ASSERT_STRING_EQUAL(Term__toString(term[0]), "19:30 [90]");
  CU_ASSERT_STRING_EQUAL(Term__toString(term[1]), "10:15 [120]");
  CU_ASSERT_STRING_EQUAL(Term__toString(term[2]), "19:45 [45]");
}

void test_earlier(){
  CU_ASSERT_TRUE(Term__earlierThan(term[1], term[0]));
  CU_ASSERT_TRUE(Term__earlierThan(term[0], term[2]));
  CU_ASSERT_FALSE(Term__earlierThan(term[2], term[1]));
}

void test_later(){
  CU_ASSERT_TRUE(Term__laterThan(term[0], term[1]));
  CU_ASSERT_TRUE(Term__laterThan(term[2], term[0]));
  CU_ASSERT_FALSE(Term__laterThan(term[1], term[2]));
}

void test_equal(){
  CU_ASSERT_TRUE(Term__equals(term[0], term[0]));
  CU_ASSERT_TRUE(Term__equals(term[1], term[1]));
  CU_ASSERT_FALSE(Term__equals(term[2], term[0]));
}

void test_end(){
  Term *tester = Term__endTerm(term[0], term[2]);
  CU_ASSERT_EQUAL(tester->duration, 15);
  CU_ASSERT_EQUAL(tester->hour, 19);
  CU_ASSERT_EQUAL(tester->minute, 30);

  free(tester);
  Term__destroy(term[0]);
  Term__destroy(term[1]);
  Term__destroy(term[2]);
  free(term);

}
//---------------------------------------------------------------------------------

int main(){
  CU_pSuite pSuite = NULL;
  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();
  pSuite = CU_add_suite("Terminy", 0,0);

  if(NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  //------------------------------testy-------------------------------
  if((NULL == CU_add_test(pSuite, "Term__init()", test_init))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__create()", test_create))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__toString()", test_string))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__earlierThan()", test_earlier))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__laterThan()", test_later))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__equals()", test_equal))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Term__endTerm()", test_end))){
    CU_cleanup_registry();
    return CU_get_error();
  }
  //-------------------------------------------------------------------

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
