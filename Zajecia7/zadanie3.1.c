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



//-------------------pomoc-----------------------
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
//-------------------------------------------------
void Queue__print(Queue* que){
  int pom=0;
  for(int i=que->pier;i<que->coun+que->pier; i++){
    pom=i;
    if(i>que->size-1)
      pom=i%que->size;
    printf("%d\n",que->element[pom]);
  }
}

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
}

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
  int n,
      s,
     nr,
    bul=1;
  char typ;
  Element pom1,
          pom2;
  scanf("%d",&n);
  Queue* czas=Queue__create(n);
  Queue* telefony=Queue__create(n);
  for(int i=0;i<n;i++){
    scanf("%c", &typ);
    if(typ=='a'){
      scanf("%d %d", &s, &nr);
      Queue__enqueue(czas, s);
      Queue__enqueue(telefony, nr);
    }
    else if(typ=='r'){
      scanf("%d", &s);
      pom1=Queue__dequeue(czas);
      pom2=Queue__dequeue(telefony);
      if(bul==1){
        printf("\nCzasy oczekiwania:\n");
        bul=0;
      }
      printf("%d %d\n",pom2, s-pom1);
    }
    else
      i--;
  }
  //Queue__print(telefony); //pokaz dynamicznego dzialania
  Queue__destroy(czas);
  Queue__destroy(telefony);
  return 0;
}
