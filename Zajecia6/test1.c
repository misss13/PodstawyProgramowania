#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} Day;
typedef enum {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;

int dl=0;

char* Day__toString(Day day){
  if(day==0)
    return "Poniedziałek";
  if(day==1)
    return "Wtorek";
  if(day==2)
    return "Środa";
  if(day==3)
    return "Czwartek";
  if(day==4)
    return "Piątek";
  if(day==5)
    return "Sobota";
  if(day==6)
    return "Niedziela";
}

Day Obsluga__Dni(char *s){
  if(!strcmp(s,"Mon"))
    return MON;
  if(!strcmp(s,"Tue"))
    return TUE;
  if(!strcmp(s,"Wed"))
    return WED;
  if(!strcmp(s,"Fri"))
    return FRI;
  if(!strcmp(s,"Sat"))
    return SAT;
  if(!strcmp(s,"Sun"))
    return SUN;
  if(!strcmp(s,"Thu"))
    return THU;
}

Day Day__nextDay(Day day){
  if(day==SUN)
    return MON;
  else
    return day+1;
}

Day Day__prevDay(Day day){
  if(day==MON)
    return SUN;
  else
    return day-1;
}

Day Day__swich(Action *actions, Day day) {
  for(int i=0; i<dl; i++){
    switch (actions[i]){
     case DAY_EARLIER:
       day = Day__prevDay(day);
       break;
     case DAY_LATER:
       day = Day__nextDay(day);
       break;
    }
  }
  return day;
}

Action* parse(int rozmiarTablicy, char *tablica[]){
  int j=0;
  Action *zwrot = malloc(rozmiarTablicy * sizeof(*zwrot));
  for(int i=0; i<rozmiarTablicy-1; i++){
    if(!strcmp(tablica[i], "d-")){
      zwrot[j] = DAY_EARLIER;
      j++;
    }
    if(!strcmp(tablica[i], "d+")){
      zwrot[j] = DAY_LATER;
      j++;
    }
    if(!strcmp(tablica[i], "t-")){
      zwrot[j] = TIME_EARLIER;
      j++;
    }
    if(!strcmp(tablica[i], "t+")){
      zwrot[j] = TIME_LATER;
      j++;
    }
  }
  dl=j; //globalna dlugosc
  return zwrot;
}

//----------------------testy-------------------------------
void test_parse(){
  dl=6;
  char *arg[]={"d+", "d+", "t-", "t+", "d-"};
  CU_ASSERT_EQUAL(Day__swich(parse(dl,arg), Obsluga__Dni("Mon")), TUE);

  dl=6;
  arg[0]="d-";
  arg[1]="aa";
  arg[2]="d-";
  arg[3]="d+";
  arg[4]="d+";
  CU_ASSERT_EQUAL(Day__swich(parse(dl,arg), Obsluga__Dni("Wed")), WED);

  arg[0]="d+";
  arg[1]="aa";
  arg[2]="d+";
  arg[3]="aa";
  arg[4]="t+";
  dl=6;
  CU_ASSERT_EQUAL(Day__swich(parse(dl,arg), Obsluga__Dni("Sat")), MON);
}

void test_toString(){
  CU_ASSERT_STRING_EQUAL(Day__toString(MON), "Poniedziałek");
  CU_ASSERT_STRING_EQUAL(Day__toString(TUE), "Wtorek");
  CU_ASSERT_STRING_EQUAL(Day__toString(WED), "Środa");
}

void test_nextDay(){
  CU_ASSERT_EQUAL(FRI, Day__nextDay(THU));
  CU_ASSERT_EQUAL(MON, Day__nextDay(SUN));
}

void test_prevDay(){
  CU_ASSERT_EQUAL(TUE, Day__prevDay(WED));
  CU_ASSERT_EQUAL(SUN, Day__prevDay(MON));
}

int main(){
  CU_pSuite pSuite = NULL;

  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("Dni_tygodnia", 0,0);
  if(NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  //---------------------------------------------------------
  if((NULL == CU_add_test(pSuite, "parse", test_parse))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "day__prevDay", test_prevDay))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "day__toString", test_toString))){
      CU_cleanup_registry();
      return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite,"day__nextDay", test_nextDay))){
    CU_cleanup_registry();
    return CU_get_error();
  }
  //---------------------------------------------------------

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
