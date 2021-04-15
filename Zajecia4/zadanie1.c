#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 1000

#include <stdio.h>
#include <stdlib.h>

void swap(int *arr, int a, int b){
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void print(int *arr, int n){
  FOR(i,n)
    printf("%d\t",arr[i]);
  printf("\n");
}

void sortowanie_przez_wybieranie(int* lista, int n){
  int dozamiany=0;
  int maxim=lista[0];
  FOR(i,n-1){
    maxim=lista[i];
    for(int j=i; j<n; j++){
      if(maxim>lista[j]){
        maxim=lista[j];
        dozamiany=j;
      }
    }
    if(dozamiany != (i-1))
      swap(lista, dozamiany, i);
    print(lista, n); //on
  }
}

int main(void){
  int tab[] = {8, 5, 4, 3, 2, 1};
  int dlugosc =*(&tab + 1) - tab;
  sortowanie_przez_wybieranie(tab, dlugosc);
  print(tab, dlugosc);
}
