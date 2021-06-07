#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


enum Day
  {
   MON,
   TUE,
   WED,
   THU,
   FRI,
   SAT,
   SUN
  };

struct Lesson
{
  char *className;
  enum Day day;
  int hour;
  int minute;
  int duration;
};

struct Node
{
  struct Lesson lesson;
  struct Node *next;
};

void List__insert(struct Node **list, struct Lesson lesson, bool begin)
{
  struct Node *new;

  new = (struct Node *)malloc(sizeof(struct Node));
  new->lesson.className = lesson.className;
  new->lesson.day = lesson.day;
  new->lesson.hour = lesson.hour;
  new->lesson.minute = lesson.minute;
  new->lesson.duration = lesson.duration;
  new->next = NULL;
  if (begin || *list == NULL)
    {
      new->next = *list;
      *list = new;
    }
  else
    {
      struct Node *current;
      current = *list;
      while(current->next != NULL)
	{
	  current = current->next;
	}
      current->next = new;
    }
}

void SortedList__insert(struct Node **list, struct Lesson lesson)
{
    struct Node *new;
    int f = 1;
    struct Node *current;
    current = *list;
    char *name = malloc(50);
    new = (struct Node *)malloc(sizeof(struct Node));
    strcpy(name, lesson.className);
    new->lesson.className = name;
    new->lesson.day = lesson.day;
    new->lesson.hour = lesson.hour;
    new->lesson.minute = lesson.minute;
    new->lesson.duration = lesson.duration;
    new->next = NULL;

    if (*list == NULL)
      {
	new->next = *list;
	*list = new;
      }
    else
      {
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

void List__remove(struct Node **list, struct Lesson lesson)
{
  struct Node *current;
  struct Node *next;
  struct Node *prev;
  
  if(!strcmp(lesson.className, list[0]->lesson.className) && lesson.day == list[0]->lesson.day && lesson.hour == list[0]->lesson.hour && lesson.minute == list[0]->lesson.minute && lesson.duration == list[0]->lesson.duration)
    {
      current = *list;
      *list = list[0]->next;
      free(current);
    }
  else
    {
      for (current = list[0]->next, prev = *list; current != NULL; prev = current, current = current->next)
	{
	  if(!strcmp(lesson.className, current->lesson.className) && lesson.day == current->lesson.day && lesson.hour == current->lesson.hour && lesson.minute == current->lesson.minute && lesson.duration == current->lesson.duration)
	    {
	      next = current->next;
	      free(current);
	      prev->next = next;
	    }
	}
    }
}

void List__print(struct Node *list)
{

  char *dayNames[] = {"Poniedziałek", "Wtorek", "Środa", "Czwartek", "Piątek", "Sobota", "Niedziela"};

  struct Node *current;
  
  for (current = list; current != NULL; current = current->next)
    {
      printf("%s, %s %02d:%02d [%d]\n", current->lesson.className, dayNames[current->lesson.day], current->lesson.hour, current->lesson.minute, current->lesson.duration);
    }
}

void List__destroy(struct Node **list)
{
  if(*list == NULL)
    {
      printf("Lista nie istnieje\n");
    }
  else
    {
      struct Node *current;
      struct Node *next;
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
int main(void){
 struct Node *list = NULL;
 struct Lesson lesson;

  lesson.className = "Podstawy Programowania";
  lesson.day = WED;
  lesson.hour = 12;
  lesson.minute = 50;
  lesson.duration = 90;
  List__insert(&list, lesson, true);

  lesson.className = "Wychowanie fizyczne";
  lesson.day = MON;
  lesson.hour = 8;
  lesson.minute = 00;
  lesson.duration = 90;
  List__insert(&list, lesson, true);

  List__print(list);
  List__remove(&list, lesson);
  List__print(list);

  List__destroy(&list);
  List__destroy(&list);
  //free(lesson.className);
  return 0;
}
