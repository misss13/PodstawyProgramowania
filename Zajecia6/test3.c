#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <CUnit/Basic.h>

typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} Day;
typedef enum {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;

typedef struct{
  int hour;
  int minute;
  int duration;
  Day day;
} Term;

typedef struct{
  Term* term;
  char* name;
} Lesson;

 struct{
  Day Dfirst;
  Day Dlast;
  int Hfirst;
  int Hlast;
  int HDlast;
}lime={MON, FRI, 8, 20, 17};
int dl=0;

//-------------------------DAY-----------------------------
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
  dl=j;
  return zwrot;
}

//-------------------------TERM----------------------------

void Term__init(Term* term, int hour, int minute, int duration, Day day){
  term->hour=hour;
  term->minute=minute;
  term->duration=duration;
  term->day=day;
}

Term* Term__create(int hour, int minute, int duration, Day day){
  Term *create=malloc(sizeof(Term));
  Term__init(create, hour, minute, duration, day);
}

void Term__destroy(Term* term){
  free(term);
}

char* Term__toString(Term* term){
  char *str=malloc(20*sizeof(char));
  snprintf(str, sizeof(str)*5, "%s %02d:%02d [%d]",Day__toString(term->day), term->hour, term->minute, term->duration);
  return str;
}

bool Term__earlierThan(Term* term1, Term *term2){
  if(term1->day < term2->day)
    return true;
  else if(term1->day == term2->day && term1->hour < term2->hour)
    return true;
  else if(term1->day == term2->day && term1->hour == term2->hour && term1->minute < term2->minute)
    return true;
  else
    return false;
}

bool Term__laterThan(Term* term1, Term *term2){
  if(term1->day > term2->day)
    return true;
  else if(term1->day == term2->day && term1->hour > term2->hour)
    return true;
  else if(term1->day == term2->day && term1->hour == term2->hour && term1->minute > term2->minute)
    return true;
  else
    return false;
}

bool Term__equals(Term* term1, Term *term2){
  if(term1->day==term2->day && term1->hour == term2->hour && term1->minute == term2->minute && term1->duration == term2->duration)
    return true;
  else
    return false;
}

Term* Term__endTerm(Term* term1, Term *term2){
  int duration = (term2->hour - term1->hour)*60;
  duration += term2->minute - term1->minute;
  Term *term=Term__create(term1->hour, term1->minute, duration > 0 ? duration : 0, term1->day);
  return term;
}
//---------------------------------Lesson-------------------------------------
Lesson* Lesson__create(int hour, int minute, int duration, Day day, char* name){
  Lesson *lesson = malloc(sizeof(Lesson));
  lesson->term = Term__create(hour, minute, duration, day);
  lesson->name = malloc(strlen(name)*sizeof(*name));
  strcpy(lesson->name, name);
  return lesson;
}

char* Lesson__toString(Lesson* lesson){
  char *str=malloc(30*sizeof(char));
  snprintf(str, sizeof(str)*10, "%s, %s", lesson->name, Term__toString(lesson->term));
  return str;
}

int Lesson__termin(Lesson* lesson){ //jak tak zwroc 0 nie 1
  int endHour = lesson->term->hour + ((lesson->term->duration + lesson->term->minute) / 60);
  int endMinute = (lesson->term->duration + lesson->term->minute) % 60;

  if(lesson->term->day >= lime.Dfirst && lesson->term->day < lime.Dlast){
    if( (lesson->term->hour > lime.Hfirst || (lesson->term->hour==lime.Hfirst && lesson->term->minute >= 0)) && (endHour < lime.Hlast || (endHour == lime.Hlast && endMinute == 0)))
      return 0;
    else
      return 1;
  }//pn-czw 8-20
  else if(lesson->term->day == lime.Dlast){
    if((lesson->term->hour > lime.Hfirst || (lesson->term->hour==lime.Hfirst && lesson->term->minute >= 0)) && (endHour < lime.HDlast || (endHour == lime.HDlast && endMinute == 0)))
      return 0;
    else
      return 1;
  }//pt 8-17
  else//sb-niedz
    return 1;
}

//------------komunikaty--------------------
void Dt(){printf("Dzień w tył\n");}
void Dp(){printf("Dzień w przód\n");}
void Tt(){printf("Termin w tył\n");}
void Tp(){printf("Termin w przód\n");}
void Pp(){printf("Przed uwzględnieniem przesunięć\n\t");}
void Po(){printf("Po uwzględnieniu przesunięć\n\t");}
void uw(Lesson* lesson){
  printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
}
//------------przesuwanie-------------------
void Lesson__earlierDay(Lesson* lesson){
  lesson->term->day=Day__prevDay(lesson->term->day);
  if(Lesson__termin(lesson)){
    lesson->term->day=Day__nextDay(lesson->term->day);
  }
}

void Lesson__laterDay(Lesson* lesson){
  lesson->term->day=Day__nextDay(lesson->term->day);
  if(Lesson__termin(lesson)){
    lesson->term->day=Day__prevDay(lesson->term->day);
  }
}

void Lesson__earlierTime(Lesson* lesson){
  lesson->term->hour+=(lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
  lesson->term->minute=(lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
  if(Lesson__termin(lesson)){
    lesson->term->hour+=(lesson->term->duration + lesson->term->minute) / 60;
    lesson->term->minute=(lesson->term->duration + lesson->term->minute) % 60;
  }
}

void Lesson__laterTime(Lesson* lesson){
  lesson->term->hour+=(lesson->term->duration + lesson->term->minute) / 60;
  lesson->term->minute=(lesson->term->duration + lesson->term->minute) % 60;
  if(Lesson__termin(lesson)){
    lesson->term->hour+=(lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
    lesson->term->minute=(lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
  }
}
//---------------------------------testy------------------------------------------

void test_EarlierDay(){
  Lesson *lesson=Lesson__create(15, 30, 60, MON, "PP");
  Lesson__earlierDay(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(15, 30, 60, MON)));
  Lesson *lesson1=Lesson__create(13, 45, 90, FRI, "PP");
  Lesson__earlierDay(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(13, 45, 90, THU)));
  Lesson__earlierDay(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(13, 45, 90, WED)));
  free(lesson);
  free(lesson1);
}

void test_LaterDay(){
  Lesson *lesson=Lesson__create(15, 30, 60, MON, "PP");
  Lesson__laterDay(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(15, 30, 60, TUE)));
  Lesson__laterDay(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(15, 30, 60, WED)));
  Lesson *lesson1=Lesson__create(14, 45, 90, FRI, "PP");
  Lesson__laterDay(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(14, 45, 90, FRI)));
  free(lesson);
  free(lesson1);
}

void test_LaterTime(){
  Lesson *lesson=Lesson__create(10, 30, 30, MON, "PP");
  Lesson__laterTime(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(11, 00, 30, MON)));
  Lesson__laterTime(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(11, 30, 30, MON)));
  Lesson *lesson1=Lesson__create(16, 50, 9, FRI, "PP");
  Lesson__laterTime(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(16, 50, 9, FRI)));
  free(lesson);
  free(lesson1);
}

void test_EarlierTime(){
  Lesson *lesson=Lesson__create(12, 00, 30, MON, "PP");
  Lesson__earlierTime(lesson);
  CU_ASSERT(Term__equals(lesson->term, Term__create(11, 30, 30, MON)));
  Lesson *lesson1=Lesson__create(15, 45, 15, WED, "PP");
  Lesson__earlierTime(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(15, 30, 15, WED)));
  Lesson__earlierTime(lesson1);
  CU_ASSERT(Term__equals(lesson1->term, Term__create(15, 15, 15, WED)));
  free(lesson);
  free(lesson1);
}

void test_String(){
  Lesson *lesson=Lesson__create(12, 30, 30, MON, "Podstawy Programowania");
  CU_ASSERT_STRING_EQUAL(Lesson__toString(lesson), "Podstawy Programowania, Poniedziałek 12:30 [30]");
  Lesson *lesson1=Lesson__create(12, 00, 60, MON, "Podstawy Programowania");
  CU_ASSERT_STRING_EQUAL(Lesson__toString(lesson1), "Podstawy Programowania, Poniedziałek 12:00 [60]");
  free(lesson);
}

Lesson* mainn(int argc, char **argv){
  Lesson *zajecia=Lesson__create(12, 50, 90, WED, "Podstawy programowania");
  argv +=1;
  Action *pokolei=parse(argc, argv);
  for(int i=0; i < dl; i++){
    switch (pokolei[i]){
    case DAY_EARLIER:
      Lesson__earlierDay(zajecia);
      break;
    case DAY_LATER:
      Lesson__laterDay(zajecia);
      break;
    case TIME_EARLIER:
      Lesson__earlierTime(zajecia);
      break;
    case TIME_LATER:
      Lesson__laterTime(zajecia);
      break;
    }
  }
  return zajecia;
}

void test_main(){
  Lesson *lesson;
  char *argc[] = {"./program3.1.c", "d+", "d+", "t+"};
  lesson = mainn(4, argc);
  CU_ASSERT(Term__equals(lesson->term, Term__create(14, 20, 90, FRI)));
  argc[3] = "d+";
  lesson = mainn(4, argc);
  CU_ASSERT(Term__equals(lesson->term, Term__create(12, 50, 90, FRI)));
  argc[1] = "t-";
  lesson = mainn(4, argc);
  CU_ASSERT(Term__equals(lesson->term, Term__create(11, 20, 90, FRI)));
}

int main(){
  CU_pSuite pSuite = NULL;
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("Lesson-testy", 0,0);
  if (NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }
  //------------------------------testy-------------------------------
  if((NULL == CU_add_test(pSuite, "Lesson__earlierDay()", test_EarlierDay))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Lesson__laterDay()", test_LaterDay))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Lesson__laterTime()", test_LaterTime))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Lesson__earlierTime()", test_EarlierTime))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Lesson__toString()", test_String))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "main()", test_main))){
    CU_cleanup_registry();
    return CU_get_error();
  }
  //--------------------------------------------------------------

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
