#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
  int hour;
  int minute;
  int duration;
} Term;

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

int main(void){
  Term* term=Term__create(9,45,90);
  Term* term2=Term__create(10,15,90);
  printf("%d\n",Term__equals(term,term2));
  Term* term3=Term__endTerm(term,term2);
  printf("%s\n",Term__toString(term3));

  Term__destroy(term);
  Term__destroy(term1);
  Term__destroy(term3);

  //printf("%s\n",Term__toString(term3));
}
