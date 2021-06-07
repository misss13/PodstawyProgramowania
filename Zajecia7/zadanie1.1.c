#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

  int n, k, pom;
  char *ptr;

  scanf("%d %d",&n ,&k);
  Stack* stosik=Stack__create(n);
  char* x=(char*)malloc(sizeof(char)*k);

  while(scanf("%s ",x) != EOF){
    if(x[0]=='\n')
      break;
    if(x[0]=='*'){
      pom=Stack__pop(stosik);
      k=Stack__pop(stosik);
      Stack__push(stosik, pom*k);
    }
    else if(x[0]=='/'){
      pom=Stack__pop(stosik);
      k=Stack__pop(stosik);
      Stack__push(stosik, k/pom);
    }
    else if(x[0]=='+'){
      pom=Stack__pop(stosik);
      k=Stack__pop(stosik);
      Stack__push(stosik, pom+k);
    }
    else if(x[0]=='-'){
      pom=Stack__pop(stosik);
      k=Stack__pop(stosik);
      Stack__push(stosik, k-pom);
    }
    else{
      pom=strtoumax(x, &ptr,10);
      Stack__push(stosik, pom);
      ptr=0;
    }
  }
  printf("Wynik: %d\n", Stack__pop(stosik));
  Stack__destroy(stosik);
  return 0;
}
