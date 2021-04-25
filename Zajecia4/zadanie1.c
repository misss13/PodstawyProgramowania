#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 1000

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void funkcja()
{
  // Tu można coś wpisać
  int i;
  for (i=0; i<10000000; ++i)
    {
      int x = atoi("300");
    }
}

int main(void){
  srand(time(NULL));
  int tab[]={1,2,3,5,3,2,3,5,8,3,1,2,3};
  heapsort(tab, 13);
  //print(tab, 13);
  /* int tab[] = {8, 5, 4, 5, 6, 0, 3, 2, 1};
  int dlugosc =*(&tab + 1) - tab;
  //sortowanie_przez_wybieranie(tab, dlugosc);
  clock_t startClock = clock();
  funkcja();
  clock_t endClock = clock();
  printf("%lf",(double) (endClock - startClock)/CLOCKS_PER_SEC);
  startClock = clock();
  funkcja();
  endClock = clock();
  printf("%lf",(double) (endClock - startClock)/CLOCKS_PER_SEC);

  heapsort(tab, dlugosc);
  
  //-----wczytywanie testu
  int z,n,c;

  scanf("%d", &z);
  FOR(i,z){
    scanf("%d %d",&n, &c);
    int *tablica = (int *)malloc( n * sizeof(int));
    FOR(j,n)
      scanf("%d", &tablica[j]);
    sortowanie_przez_wybieranie(tablica, n);
    print(tablica, n);
    free(tablica);
  }
  */
  //------losowe_liczby
  int N=10; //zestawow dla 100000 kilka s, sprawdzaj z 10000
  int n, z, a;
  clock_t start, stop, t_wstaw, t_szybkie, t_heap;
  t_wstaw=0;
  t_szybkie=0;
  t_heap=0;
  printf("%d\n",N);
  FOR(i,N){
    n=rand()%100+2; //liczb w tablicy
    printf("%d 1\n",n);
    int *tablica1 = (int *)malloc( n * sizeof(int));
    int *tablica2 = (int *)malloc( n * sizeof(int));
    int *tablica3 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z=rand();
      printf("%d", z);
      tablica1[j]=z;
      tablica2[j]=z;
      tablica3[j]=z;
    }
    //wstaw
    start=clock();
    sortowanie_przez_wybieranie(tablica1, n);
    stop=clock();
    t_wstaw+=stop-start;
    //szybkie
    start=clock();
    quicksort(tablica2, 0, n-1);
    stop=clock();
    t_szybkie+=stop-start;
    //heap
    start=clock();
    quicksort(tablica3,0, n-1);
    stop=clock();
    t_heap+=stop-start;
    //free
    free(tablica1);
    free(tablica2);
    free(tablica3);
  }/*
  printf("Sortowanie: wybieranie\t losowe dane\t %lf\n", (double)(t_wstaw)/CLOCKS_PER_SEC);
  printf("Sortowanie: szybkie   \t losowe dane\t %lf\n", (double)(t_szybkie)/CLOCKS_PER_SEC);
  printf("Sortowanie: kopcowanie\t losowe dane\t %lf\n", (double)(t_heap)/CLOCKS_PER_SEC);

  //-------prawie posortowane malejaco
  t_wstaw=0;
  t_szybkie=0;
  t_heap=0;
  z=0;
  FOR(i,N){
    n=rand()%10+2; //liczb w tablicy
    int *tablica1 = (int *)malloc( n * sizeof(int));
    int *tablica2 = (int *)malloc( n * sizeof(int));
    int *tablica3 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z+=rand()%500;
      tablica1[j]=z;
      tablica2[j]=z;
      tablica3[j]=z;
    }
    //prawie bo zamieniam 2 el miejscami
    swap(tablica1, 0, n/2);
    swap(tablica2, 0, n/2);
    swap(tablica3, 0, n/2);
    z=(n-1);
    //wstaw
    start=clock();
    sortowanie_przez_wybieranie(tablica1, n);
    stop=clock();
    t_wstaw+=stop-start;
    //szybkie
    start=clock();
    quicksort(tablica2, 0, z);
    stop=clock();
    t_szybkie+=stop-start;
    //heap
    start=clock();
    heapsort(tablica3, n);
    stop=clock();
    t_heap+=stop-start;
    //free
    free(tablica1);
    free(tablica2);
    free(tablica3);

  }
    printf("Sortowanie: wybieranie\t losowe pr pos rosnaco\t %lf\n", (double)(t_wstaw)/CLOCKS_PER_SEC);
    printf("Sortowanie: szybkie   \t losowe pr pos rosnaco\t %lf\n", (double)(t_szybkie)/CLOCKS_PER_SEC);
    printf("Sortowanie: kopcowanie\t losowe pr pos rosnaco\t %lf\n", (double)(t_heap)/CLOCKS_PER_SEC);

//-------posortowane rosnaco
  t_wstaw=0;
  t_szybkie=0;
  t_heap=0;
  z=0;
  FOR(i,N){
    n=rand()%10+2; //liczb w tablicy
    int *tablica1 = (int *)malloc( n * sizeof(int));
    int *tablica2 = (int *)malloc( n * sizeof(int));
    int *tablica3 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z+=rand()%500;
      z%=1000000;
      tablica1[j]=z;
      tablica2[j]=z;
      tablica3[j]=z;
    }
    //wstaw
    start=clock();
    sortowanie_przez_wybieranie(tablica1, n);
    stop=clock();
    t_wstaw+=stop-start;
    //szybkie
    start=clock();
    quicksort(tablica2, 0, n-1);
    stop=clock();
    t_szybkie+=stop-start;
    //heap
    start=clock();
    heapsort(tablica3, n);
    stop=clock();
    t_heap+=stop-start;
    //free
    free(tablica1);
    free(tablica2);
    free(tablica3);

  }
    printf("Sortowanie: wybieranie\t losowe pos rosnaco\t %lf\n", (double)(t_wstaw)/CLOCKS_PER_SEC);
    printf("Sortowanie: szybkie   \t losowe pos rosnaco\t %lf\n", (double)(t_szybkie)/CLOCKS_PER_SEC);
    printf("Sortowanie: kopcowanie\t losowe pos rosnaco\t %lf\n", (double)(t_heap)/CLOCKS_PER_SEC);
//-------prawie posortowane malejaco
  t_wstaw=0;
  t_szybkie=0;
  t_heap=0;
  z=500000+rand();
  FOR(i,N){
    n=rand()%10+2; //liczb w tablicy
    int *tablica1 = (int *)malloc( n * sizeof(int));
    int *tablica2 = (int *)malloc( n * sizeof(int));
    int *tablica3 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z-=rand()%500;
      tablica1[j]=z;
      tablica2[j]=z;
      tablica3[j]=z;
    }
    //prawie bo zamieniam 2 el miejscami
   
    //wstaw
    start=clock();
    sortowanie_przez_wybieranie(tablica1, n);
    stop=clock();
    t_wstaw+=stop-start;
    //szybkie
    start=clock();
    quicksort(tablica2, 0, n-1);
    stop=clock();
    t_szybkie+=stop-start;
    //heap
    start=clock();
    heapsort(tablica3, n);
    stop=clock();
    t_heap+=stop-start;
    //free
    free(tablica1);
    free(tablica2);
    free(tablica3);

  }
    printf("Sortowanie: wybieranie\t losowe pr pos malejaco\t %lf\n", (double)(t_wstaw)/CLOCKS_PER_SEC);
    printf("Sortowanie: szybkie   \t losowe pr pos malejaco\t %lf\n", (double)(t_szybkie)/CLOCKS_PER_SEC);
    printf("Sortowanie: kopcowanie\t losowe pr pos malejaco\t %lf\n", (double)(t_heap)/CLOCKS_PER_SEC);
   */
}
