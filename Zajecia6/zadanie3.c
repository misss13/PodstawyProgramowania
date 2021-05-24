#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

//-------------------------TERM----------------------------
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
void uw(Lesson* lesson){
  printf("Zajęcia \"%s\" nie mogą być przesunięte na termin \"%s\"\n", lesson->name, Term__toString(lesson->term));
}
//------------przesuwanie-------------------
void Lesson__earlierDay(Lesson* lesson){
  lesson->term->day=Day__prevDay(lesson->term->day);
  Dt();
  if(Lesson__termin(lesson)){
    uw(lesson);
    lesson->term->day=Day__nextDay(lesson->term->day);
  }
}

void Lesson__laterDay(Lesson* lesson){
  lesson->term->day=Day__nextDay(lesson->term->day);
  Dp();
  if(Lesson__termin(lesson)){
    uw(lesson);
    lesson->term->day=Day__prevDay(lesson->term->day);
  }
}

void Lesson__earlierTime(Lesson* lesson){
  lesson->term->hour+=(lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
  lesson->term->minute=(lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
  Tt();
  if(Lesson__termin(lesson)){
    uw(lesson);
    lesson->term->hour+=(lesson->term->duration + lesson->term->minute) / 60;
    lesson->term->minute=(lesson->term->duration + lesson->term->minute) % 60;
  }
}

void Lesson__laterTime(Lesson* lesson){
  lesson->term->hour += (lesson->term->duration + lesson->term->minute) / 60;
  lesson->term->minute = (lesson->term->duration + lesson->term->minute) % 60;
  Tp();
  if(Lesson__termin(lesson)){
    uw(lesson);

    lesson->term->hour += (lesson->term->minute - lesson->term->duration) < 0 ? ((lesson->term->minute - lesson->term->duration) % 60 ? ((lesson->term->minute - lesson->term->duration) / 60) - 1 : (lesson->term->minute - lesson->term->duration) / 60) : 0;
    lesson->term->minute = (lesson->term->minute - lesson->term->duration ) >= 0 ? (lesson->term->minute - lesson->term->duration ) : 60-((lesson->term->duration - lesson->term->minute) % 60);
  }
}

int main(void){
  // Term* term=Term__create(9,45,90, MON);
  //Term* term2=Term__create(10,15,90, WED);
  //Term* term3=Term__endTerm(term,term2);
  //printf("%s\n", Term__toString(term));
  //Term__destroy(term);
  //Term__destroy(term2);
  //Term__destroy(term3);
  Lesson* zajecia=Lesson__create(12, 50, 90, WED, "Podstawy Programowania");
  Lesson__earlierDay(zajecia);
  Lesson__laterTime(zajecia);
  Lesson__laterTime(zajecia);
  Lesson__laterTime(zajecia);
  Lesson__laterTime(zajecia);
  printf("%s\n", Lesson__toString(zajecia));
  printf("%d", lime.Hfirst);
}
