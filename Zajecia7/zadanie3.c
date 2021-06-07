#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INT_MIN -2
#ifndef max
#define max(a,b) ((a) > (b) ? (a) : (b))
#endif

int dynamic=-10;

typedef int Element;
typedef struct {
  int size;
  int pier;
  int ostat;
  int coun;
  int * element;
} Queue;

//-----pomoc-------
int Queue__pocz(Queue* kol){
  return kol->element[kol->pier];
}
int Queue__isEmpty(Queue* kol){
  return kol->coun==0;
}

bool Queue__isFull(Queue* kol){
  return kol->coun==kol->size;
}

int Queue__size(Queue* kol){
  return kol->coun;
}
void Queue__print(Queue* que){
  int pom=0;
  for(int i=que->pier;i<que->coun+que->pier; i++){
    pom=i;
    if(i>que->size-1)
      pom=i%que->size;
    printf("%d\n",que->element[pom]);
  }
}
//-----------------
void Queue__enqueue(Queue *queue, Element element){
  if(!Queue__isFull(queue)){
    if(queue->ostat == queue->size-1)
      queue->ostat = -1;
    queue->element[++queue->ostat]=element;
    queue->coun++;
    dynamic=max(dynamic, queue->coun);
    if(queue->coun<queue->size)
      queue->element=realloc(queue->element, sizeof(int)*(dynamic+1));
  }
}//1 |2 | | | | | | |max

Queue *Queue__create(int size){
  Queue* kol=malloc(sizeof(Queue));
  kol->size=size;
  kol->pier=0;
  kol->ostat=-1;
  kol->coun=0;
  kol->element=calloc(1, 0);
  return kol;
}

void Queue__destroy(Queue *queue){
  if(!queue->element){
    printf("Kolejka nie istnieje!\n");
  }
  else{
    free(queue);
    free(queue->element);
    queue->element=NULL;
  }
}
Element Queue__dequeue(Queue* queue){
  if(Queue__isEmpty(queue))
    return INT_MIN;
  Element ret=queue->element[queue->pier++];
  if(queue->pier == queue->size)
    queue->pier=0;
  queue->coun--;
  return ret;
}

int main(void){
  Queue *queue = Queue__create(1);
  queue->element=NULL;

  Element liczba = Queue__dequeue(queue);
  printf("%d\n", liczba);
  printf("---------\n");
  Queue__destroy(queue);
  queue = Queue__create(3);
  Queue__enqueue(queue, 3);
	Queue__enqueue(queue, 5);
  Queue__enqueue(queue, 2);
  Queue__enqueue(queue, 4);
  Queue__print(queue);
  printf("---------\n");
  liczba = Queue__dequeue(queue);
	printf("%d\n", liczba);
  printf("---------\n");
  Queue__print(queue);

  Queue__destroy(queue);
  Queue__destroy(queue);
  return 0;
}
