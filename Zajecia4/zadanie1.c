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
    printf("%d\t",arr[i]);
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
/*
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
  }
}
*/
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
  srand(time(NULL));

  //-----wczytywanie testu
  char dane[50];
  int z,n;
  clock_t start, stop, wybieranie, quick, heap;

  scanf("%d", &z);
   FOR(k,5){
     wybieranie=0;
     quick=0;
     heap=0;
     //scanf("%d", &z);
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
      start=clock();
      sortowanie_przez_wybieranie(tablica, n);
      stop=clock();
      wybieranie+=stop-start;

      //szybkie
      start=clock();
      quicksort(tablica1, 0, n-1);
      stop=clock();
      quick+=stop-start;

      //heap
      start=clock();
      heapsort(tablica2, n);
      stop=clock();
      heap+=stop-start;

      //print debug
      //print(tablica, n);
      //print(tablica1, n);
      //print(tablica2, n);

      //free
      free(tablica);
      free(tablica1);
      free(tablica2);
    }
    if(k==0)
      strcpy(dane, "losowe");
    if(k==1)
      strcpy(dane, "pr rosn");
    if(k==2)
      strcpy(dane, "rosnace");
    if(k==3)
      strcpy(dane, "pr male");
    if(k==4)
      strcpy(dane,"malejace");

    printf("Sortowanie: wybieranie\t %s dane\t %lf\n",dane, (double)(wybieranie)/CLOCKS_PER_SEC);
    printf("Sortowanie: szybkie   \t %s dane\t %lf\n",dane, (double)(quick)/CLOCKS_PER_SEC);
    printf("Sortowanie: kopcowanie\t %s dane\t %lf\n",dane, (double)(heap)/CLOCKS_PER_SEC);
  }
}
