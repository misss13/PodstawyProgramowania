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
}

void insertLast(Lesson lesson, Node** head){
  Node* link = (Node*) malloc(sizeof(Node));
  link->lesson=Lesson__create(lesson.day, lesson.className, lesson.hour, lesson.minute, lesson.duration);
  if((*head)==0){
    *head = link;
    return;
  }
  Node* current=(*head);
  while (current->next != NULL)
    current = current->next;
  current->next=malloc(sizeof(Node));
  current->next = link;
}

int Lesson__isEqual(Lesson l1, Lesson l2){
  return ((l1.day == l2.day) && (l1.hour == l2.hour)&&(l1.minute == l2.minute)&&(l1.duration == l2.duration) &&(!strcmp(l1.className, l2.className)));
}

//----------------------------------------------------
void List__insert(Node** list, Lesson lesson, bool begin){
  if(begin==1){
    insertFirst(lesson, list);
  }
  if(begin==0){
    insertLast(lesson, list);
  }
}

void List__print(Node* head){
  Node * current = head;
  while (current != NULL) {
    printf("Przedmiot: \e[31m%s\e[0m\nDzień tygodnia: \e[31m%s\e[0m\nGodzina rozpoczęcia [Czas trwania]: \e[31m%02d:%02d [%d]\e[0m\n\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    current = current->next;
  }
  free(current);
  current=NULL;
}

void List__destroy(struct Node **list){
  if((*list) == NULL){
    printf("Lista nie istenieje!\n");
    return;
  }
  Node *temp= *list;

  if(temp->next != NULL){
    Node *current = temp->next;
    while(current != NULL){
      free(current);
      current=current->next;
    }
  }
  free(*list);
  (*list)=NULL;
}

void List__remove(Node **list, Lesson lesson){
  if((*list) == NULL){
    printf("Błąd nie ma takiej listy!\n");
    return;
  }
  Node *temp=*list, *pop;
  if(temp!=NULL && Lesson__isEqual(temp->lesson, lesson)){
    *list=temp->next;
    free(temp);
    temp=NULL;
    return;
  }

  while(temp!=NULL && !Lesson__isEqual(temp->lesson, lesson)){
    pop=temp;
    temp=temp->next;
  }
  if(temp==NULL)
    return;
  pop->next=temp->next;
  free(temp);
}

int main(void){
  Node *lista = NULL;
  Lesson lesson;

  lesson.className = "Podstawy Programowania";
  lesson.day = WED;
  lesson.hour = 12;
  lesson.minute = 50;
  lesson.duration = 90;
  //insertFirst(lesson, &lista);
  List__insert(&lista, lesson, 1);
  lesson.className = "Wychowanie fizyczne";
  lesson.day = MON;
  lesson.hour = 8;
  lesson.minute = 00;
  lesson.duration = 90;
  insertFirst(lesson, &lista);

  lesson.className = "Plastyka";
  lesson.day = MON;
  lesson.hour = 7;
  lesson.minute = 00;
  lesson.duration = 60;
  insertLast(lesson, &lista);
  List__print(lista);
  //printf("%d",Lesson__isEqual(lesson, lesson));
  List__remove(&lista, lesson);
  List__print(lista);

  List__destroy(&lista);
  List__destroy(&lista);
  return 0;
}
