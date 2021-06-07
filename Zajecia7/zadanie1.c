#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INT_MIN -1

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
  stack->elements=calloc(1, 0); //jeden element o rozmiarze 0 !
  return stack;
}

void Stack__destroy(Stack *stack){
  if(!stack->elements){
    printf("Stos nie istnieje\n");
  }
  else{
    free(stack);
    free(stack->elements);
    stack->elements=NULL;
  }
}

void Stack__push(Stack* stack, int number){
  int pom=1;
  if(stack->top==-1)
    pom=2;

  if(Stack__isFull(stack)){
    printf("Stos jest już pełny! Niczego nie dokladam\n");
  }
  else{
    stack->elements=realloc(stack->elements, (stack->top+pom)*sizeof(int));
    stack->elements[++stack->top]=number;
  }
}

int Stack__pop(Stack* stack){
  int pom=1,
      ret=0;

  if(stack->top==0)
    pom=0;

  if(Stack__isEmpty(stack)){
    printf("Stos jest pusty!\n");
    return INT_MIN;
  }
  ret=stack->elements[stack->top]; //bo top to index ale +1 to il elem
  stack->elements=realloc(stack->elements, (stack->top+1-pom)*sizeof(int));
  stack->top--;
  return ret;
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

  Stack *stack=Stack__create(1);
  stack->elements=NULL;
  //int *stack = NULL;u mnie stack->elements to stack, size nie okresla wielkosci tablicy tylko jest sb zapisanym intem tam wyzej
  Stack__destroy(stack);
  stack = Stack__create(3);
  Stack__push(stack, 3);
  Stack__push(stack, 5);
  Stack__push(stack, 2);
  Stack__push(stack, 4);
  Stack__print(stack);
  printf("----------\n");
  printf("%d\n", Stack__pop(stack));
  printf("----------\n");
  Stack__print(stack);
  printf("----------\n");
  printf("%d\n", Stack__pop(stack));
  printf("%d\n", Stack__pop(stack));
  int liczba = Stack__pop(stack);
  Stack__destroy(stack);
  Stack__destroy(stack);
  return 0;
}
