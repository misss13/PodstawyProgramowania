#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 1000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static inline void swap(int *arr, int a, int b){
  int temp = arr[a];
  arr[a] = arr[b];
  arr[b] = temp;
}

void print(int *arr, int n){
  FOR(i,n)
    printf("%d\n",arr[i]);
  printf("\n");
}

void sortowanie_przez_wybieranie(int* lista, int n){
  int mini;
  for(int i=0; i<n-1; i++){
    mini=i;
    for(int j=i+1; j<n; j++){
      if(lista[j]<lista[mini])
        mini=j;
    }
    swap(lista, mini, i);
  }
}

int partition(int* tab, int p, int r){ //metoda Lomuto
  int x=tab[r];
  int i=p-1;
  for(int j=p; j<=r-1; j++){
    if(tab[j]<x){
      i++;
      swap(tab, i, j);
    }
  }
  if(tab[i+1]!=tab[r])
    swap(tab, i+1, r);
  return (i+1);
}

void quicksort(int* tab, int p, int r){
  if(p<r){
    int q=partition(tab, p, r);
    quicksort(tab, p, q-1);
    quicksort(tab, q+1, r);
  }
}

void maxheapify(int* tab, int i, int n){
  int l=1+i*2;
  int r=2+(i*2);
  int largest=i;
  if(l<n && tab[l]>tab[largest])
    largest=l;
  if(r<n && tab[r]>tab[largest])
    largest=r;
  if(largest!=i){
    swap(tab, i, largest);
    maxheapify(tab, largest, n);
  }
}

void heapsort(int *tab, int n){
  for(int i=n/2 - 1; i >= 0; i--)
    maxheapify(tab, i, n);
  for(int i=n-1; i>0; i--){
    swap(tab, 0, i);
    maxheapify(tab, 0, i);
  }
}

int main(void){

  //-----wczytywanie testu
  int z,n,c;

  scanf("%d", &z);
  FOR(i,z){
    scanf("%d",&n);
    int *tablica = (int *)malloc( n * sizeof(int));
    int *tablica1 = (int *)malloc( n * sizeof(int));
    int *tablica2 = (int *)malloc( n * sizeof(int));

    FOR(j,n){
      scanf("%d", &tablica[j]);
      tablica1[j]=tablica[j];
      tablica2[j]=tablica[j];
      //printf("%d\n", tablica[j]); //debug DLA MALYCH TESTOW
    }
    //wybieranie
    sortowanie_przez_wybieranie(tablica, n);

    //szybkie
    quicksort(tablica1, 0, n-1);

    //heap
    heapsort(tablica2, n);

    //print debug

    print(tablica, n);
    //print(tablica1, n);
    //print(tablica2, n);

    //free
    free(tablica);
    free(tablica1);
    free(tablica2);
  }
}
