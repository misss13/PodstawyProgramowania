#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} Day;

typedef struct{
  char *className;
  Day day;
  int hour;
  int minute;
  int duration;
} Lesson;

typedef struct{
  Lesson lesson;
  struct Node * next;
} Node;

char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};
//-----------------pomocnicze-------------------------
Lesson Lesson__create(Day day, char* name, int hour, int minute, int duration){
  Lesson lesson;
  lesson.className = malloc(strlen(name)*sizeof(*name));
  strcpy(lesson.className, name);
  lesson.day=day;
  lesson.hour=hour;
  lesson.minute=minute;
  lesson.duration=duration;
  return lesson;
}

void insertFirst(Lesson lesson, Node** head){
  Node* link = (Node*) malloc(sizeof(Node));
  link->lesson=Lesson__create(lesson.day, lesson.className, lesson.hour, lesson.minute, lesson.duration);
  link->next=(*head);
  (*head)=link;
  // printf("Pointer to head: %p\n", ( *head));
  // return link;
}

void insertLast(Lesson lesson, Node** head){
  Node* link = (Node*) malloc(sizeof(Node));
  link->lesson=Lesson__create(lesson.day, lesson.className, lesson.hour, lesson.minute, lesson.duration);
  if ((*head)==0){
    *head = link;
    return;
  }
  Node* current=(*head);
  while (current->next != NULL)
    current = current->next;
  current->next=malloc(sizeof(Node));
  current->next = link;
  // current->next->next=NULL;
}
//----------------------------------------------------
void List__insert(Node* list, Lesson lesson, bool begin){
  if(begin==1){
    insertFirst(lesson, list);
  }
  if(begin==0){
    printf("");
  }
}

void List__print(Node* head) {
  Node * current = head;
  //printf("P: %s %d\n", current->lesson.className, current->lesson.hour);

  while (current != NULL) {
    printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\n\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);

    printf("Pointer to element: %p\n", current);
    current = current->next;
  }
}

int main(void){
  Node *lista = NULL;
  Lesson lesson;

  lesson.className = "Podstawy Programowania";
  lesson.day = WED;
  lesson.hour = 12;
  lesson.minute = 50;
  lesson.duration = 90;
  insertFirst(lesson, &lista);
  printf("Pointer to lista: %p\n", lista);
  //List__print(lista);
  lesson.className = "Wychowanie fizyczne";
  lesson.day = MON;
  lesson.hour = 8;
  lesson.minute = 00;
  lesson.duration = 90;
  insertFirst(lesson, &lista);
  //List__print(lista);
  lesson.className = "Plastyka";
  lesson.day = MON;
  lesson.hour = 7;
  lesson.minute = 00;
  lesson.duration = 60;
  insertLast(lesson, &lista);
  List__print(lista);
  return 0;
}
