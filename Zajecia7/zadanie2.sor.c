#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum Day {MON, TUE, WED, THU, FRI, SAT, SUN};

struct Lesson{
  char *className;
  enum Day day;
  int hour;
  int minute;
  int duration;
};

struct Node{
  struct Lesson lesson;
  struct Node * next;
};

char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

//-----------------pomocnicze-------------------------
void insertFirst(struct Lesson lesson, struct Node** head){
  struct Node* new = (struct Node*) malloc(sizeof(struct Node));
  new->lesson.className = lesson.className;
  new->lesson.day = lesson.day;
  new->lesson.hour = lesson.hour;
  new->lesson.minute = lesson.minute;
  new->lesson.duration = lesson.duration;
  new->next=(*head);
  (*head)=new;
}

void insertLast(struct Lesson lesson, struct Node** head){
  struct Node* new = (struct Node*) malloc(sizeof(struct Node));
  char *name = malloc(50);
  new = (struct Node *)malloc(sizeof(struct Node));
  strcpy(name, lesson.className);
  new->lesson.className = name;
  new->lesson.day = lesson.day;
  new->lesson.hour = lesson.hour;
  new->lesson.minute = lesson.minute;
  new->lesson.duration = lesson.duration;
  new->next = NULL;
  if((*head)==0){
    *head = new;
    return;
  }
  struct Node* current=(*head);
  while (current->next != NULL)
    current = current->next;
  current->next = new;
}

int Lesson__isEqual(struct Lesson l1,struct Lesson l2){
  return ((l1.day == l2.day) && (l1.hour == l2.hour)&&(l1.minute == l2.minute)&&(l1.duration == l2.duration) &&(!strcmp(l1.className, l2.className)));
}

//----------------------------------------------------
void List__insert(struct Node** list, struct Lesson lesson, bool begin){
  struct Node* new = (struct Node *)malloc(sizeof(struct Node));
  new->lesson.className = lesson.className;
  new->lesson.day = lesson.day;
  new->lesson.hour = lesson.hour;
  new->lesson.minute = lesson.minute;
  new->lesson.duration = lesson.duration;
  new->next = NULL;
  if(begin==1){
    new->next=(*list);
    (*list)=new;

  }
  if(begin==0){
    if((*list)==0){
      *list = new;
      return;
    }
    struct Node* current=(*list);
    while (current->next != NULL)
      current = current->next;
    current->next = new;

  }
}
void List__print(struct Node* head){
  struct Node * current = head;
  while (current != NULL) {
    printf("\e[31m%s\e[0m, \e[31m%s\e[0m \e[31m%02d:%02d [%d]\e[0m\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    current = current->next;
  }
}

void List__destroy(struct Node **list)
{
  if(*list == NULL){
    printf("Lista nie istnieje!\n");
    return;
  }
  struct Node *current;
  struct Node *next;
  current = *list;
  while(current != NULL){
      next = current->next;
      free(current);
      current = next;
    }
  *list = NULL;
  free(*list);
}

void SortedList__insert(struct Node **list,struct Lesson lesson){
  struct Node *new, *current;
  int pom = 1;
  current = *list;
  new = (struct Node *)malloc(sizeof(struct Node));
  new->lesson.className = lesson.className;
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
      pom = 0;
    }
    else if(current->lesson.day == new->lesson.day){
      if(current->lesson.hour > new->lesson.hour){
        pom = 0;
      }
      else if(current->lesson.hour == new->lesson.hour){
        if(current->lesson.minute > new->lesson.minute){
          pom = 0;
        }
        else if(current->lesson.minute == new->lesson.minute){
          pom = 2;
        }
      }
    }
    if (pom == 0){
      new->next = *list;
      *list = new;
    }
    else if(pom == 1){
      while(pom == 1){
        if(current->next == NULL){
          pom = 0;
        }
        else{
          current = current->next;
          if(current->lesson.day > new->lesson.day){
            pom = 0;
          }
          else if(current->lesson.day == new->lesson.day){
            if(current->lesson.hour > new->lesson.hour){
              pom = 0;
            }
            else if(current->lesson.hour == new->lesson.hour){
              if(current->lesson.minute > new->lesson.minute){
                pom = 0;
              }
              else if(current->lesson.minute == new->lesson.minute){
                break;
              }
            }
          }
        }
        if(pom == 0){
          new->next = current->next;
          current->next = new;
          break;
        }
      }
    }
  }
}

void List__remove(struct Node **list, struct Lesson lesson){
  if((*list) == NULL){
    printf("Błąd nie ma takiej listy!\n");
    return;
  }
  struct Node *temp=*list, *pop;
  if(temp!=NULL && Lesson__isEqual(temp->lesson, lesson)){
    *list=temp->next;
    free(temp->lesson.className);
    free(temp);
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
    struct Node *list = NULL;
    struct Node *list_nieu=NULL;
    struct Lesson lesson;

    lesson.className = "Podstawy Programowania";
    lesson.day = WED;
    lesson.hour = 12;
    lesson.minute = 50;
    lesson.duration = 90;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, true);

    lesson.className = "Wychowanie fizyczne";
    lesson.day = MON;
    lesson.hour = 8;
    lesson.minute = 00;
    lesson.duration = 90;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, true);

    lesson.className = "Plastyka";
    lesson.day = MON;
    lesson.hour = 7;
    lesson.minute = 00;
    lesson.duration = 60;
    SortedList__insert(&list, lesson);
    List__insert(&list_nieu, lesson, false);

    List__print(list);
    printf("--------------------------------------\n");
    List__print(list_nieu);
    //List__remove(&list, lesson);

    List__destroy(&list);
    List__destroy(&list_nieu);

    return 0;
}
