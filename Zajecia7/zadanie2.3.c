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
  Node* new = (Node*) malloc(sizeof(Node));
  new->lesson.className = lesson.className;
  new->lesson.day = lesson.day;
  new->lesson.hour = lesson.hour;
  new->lesson.minute = lesson.minute;
  new->lesson.duration = lesson.duration;
  //link->lesson=Lesson__create(lesson.day, lesson.className, lesson.hour, lesson.minute, lesson.duration);
  new->next=(*head);
  (*head)=new;
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
    printf("\e[31m%s\e[0m, \e[31m%s\e[0m \e[31m%02d:%02d [%d]\e[0m\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    current = current->next;
  }
}

void List__destroy(Node **list){
  if((*list) == NULL){
    printf("Lista nie istenieje!\n");
    return;
  }
  Node *temp= *list;

  if(temp->next != NULL){
    Node *current = temp->next;
    while(current != NULL){
      free(current->lesson.className);
      free(current->next);
      free(current);
      current=current->next;
    }
  }
  free(*list);
  (*list)=NULL;
 }
/*
void List__destroy(Node **list)
{
  if(*list == NULL)
    {
      printf("Lista nie istnieje\n");
      return;
    }
  else
    {
      Node *current;
      Node *next;
      current = *list;

      while(current != NULL)
        {
          next = current->next;
          free(current);
          current = next;
        }

      *list = NULL;
    }
}
*/
void SortedList__insert(Node **list, Lesson lesson)
{
  Node *new, *current;
    int f = 1;
    current = *list;
    char *name = malloc(50);
    new = (Node *)malloc(sizeof(Node));
    strcpy(name, lesson.className);
    new->lesson.className = name;
    new->lesson.day = lesson.day;
    new->lesson.hour = lesson.hour;
    new->lesson.minute = lesson.minute;
    new->lesson.duration = lesson.duration;
    new->next = NULL;

    if(*list == NULL){
      new->next = *list;
      *list = new;
    }
    else{
      if(current->lesson.day > new->lesson.day){
        f = 0;
      }
      else if(current->lesson.day == new->lesson.day)
        {
          if(current->lesson.hour > new->lesson.hour)
            {
              f = 0;
            }
          else if(current->lesson.hour == new->lesson.hour)
            {
              if(current->lesson.minute > new->lesson.minute)
                {
                  f = 0;
                }
              else if(current->lesson.minute == new->lesson.minute)
                {
                  f = 2;
                }
            }
        }
      if (f == 0)
        {
          new->next = *list;
          *list = new;
        }
      else if(f == 1)
        {
          while(f == 1)
            {
              if(current->next == NULL)
                {
                  f = 0;
                }
              else
                {
                  current = current->next;
                  if(current->lesson.day > new->lesson.day)
                    {
                      f = 0;
                    }
                  else if(current->lesson.day == new->lesson.day)
                    {
                      if(current->lesson.hour > new->lesson.hour)
                        {
                          f = 0;
                        }
                      else if(current->lesson.hour == new->lesson.hour)
                        {
                          if(current->lesson.minute > new->lesson.minute)
                            {
                              f = 0;
                            }
                          else if(current->lesson.minute == new->lesson.minute)
                            {
                              break;
                            }
                        }
                    }
                }
              if(f == 0)
                {
                  new->next = current->next;
                  current->next = new;
                  break;
                }
            }
        }
    }
}

void List__remove(Node **list, Lesson lesson){
  if((*list) == NULL){
    printf("Błąd nie ma takiej listy!\n");
    return;
  }
  Node *temp=*list, *pop;
  if(temp!=NULL && Lesson__isEqual(temp->lesson, lesson)){
    *list=temp->next;
    //free(temp->lesson.className);
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
    Node *list = NULL;
    Node *list_nieu=NULL;
    Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, 0);

    lesson.className = "Wychowanie fizyczne";
    lesson.day = MON;
    lesson.hour = 8;
    lesson.minute = 00;
    lesson.duration = 90;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, 0);

    lesson.className = "Plastyka";
    lesson.day = MON;
    lesson.hour = 7;
    lesson.minute = 00;
    lesson.duration = 60;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, 0);

    List__print(list);
    printf("\n--------aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa--------\n");
    List__print(list_nieu);
    //List__remove(&list, lesson);

    List__destroy(&list);
    List__destroy(&list_nieu);

    return 0;
}
