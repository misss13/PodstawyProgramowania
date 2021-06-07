#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
  int top;
  int size;
  int* elements;
} Stack;

//----------------pomocnicze----------------
int Stack__size(Stack* stack){
  return stack->top+1;
}

int Stack__isEmpty(Stack* stack){
  return stack->top == -1;
}

int Stack__isFull(Stack* stack){
  return Stack__size(stack) == stack->size;
}

void print(Stack* stack){
  int n=stack->top;
  printf("[");
  for(int i=0; i<n; i++)
    printf("%d, ", stack->elements[i]);
  printf("%d]\n", stack->elements[n]);
}
//------------------------------------------

Stack *Stack__create(int size){
  if(size==0){
    fprintf(stderr, "Nie mogę utworzyć stosu o podanym rozmiarze\n");
    exit(EXIT_FAILURE);
  }
  Stack* stack=malloc(sizeof(Stack));
  stack->top=-1;
  stack->size=size;
  stack->elements=calloc(1, 0); //jeden element o rozmiarze 0
  return stack;
}

void Stack__destroy(Stack *stack){

  if(!stack->elements){
    fprintf(stderr, "Nie istnieje stos o takiej nazwie\n");
    exit(EXIT_FAILURE);
  }
  free(stack->elements);
  stack->elements=NULL;
  free(stack);
}
void Stack__push(Stack* stack, int number){
  int pom=1;
  if(stack->top==-1)
    pom=2;

  if(Stack__isFull(stack)){
    printf("Stos jest już pełny!\n");
  }
  else{
    stack->elements=realloc(stack->elements, (stack->top+pom)*sizeof(int));
    stack->elements[++stack->top]=number;
  }
}

int Stack__pop(Stack* stack){
  int pom=1;
  if(stack->top==0 || stack->top==-1)
    pom=0;
  if(Stack__isEmpty(stack)){
    printf("Stos jest pusty!\n");
    return -1;
  }
  stack->elements=realloc(stack->elements, (stack->top+1-pom)*sizeof(int));
  return stack->elements[stack->top--]; //bo top to index ale +1 to il elem
}

void Stack__print(Stack *stack){
  if(!Stack__isEmpty(stack)){
  int pom=stack->top;
  for(int i=pom; i>=0; i--)
    printf("%d\n",stack->elements[i]);
  }
}
//------------------------------------------

int main(void){
  int n=2;
  Stack* stosik=Stack__create(n);
  Stack__push(stosik,5);
  Stack__push(stosik,3);
  Stack__print(stosik);
  // printf(" %d\n  ",Stack__pop(stosik));
  Stack__pop(stosik);
  Stack__pop(stosik);
  //print(stosik);
  Stack__destroy(stosik);
  //Stack__destroy(stosik);
  //free(stosik);
  //widac ze przy 2 destroy blad przy destroy+free blad bo podwojne zwolnienie!
}
