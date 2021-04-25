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


int main(void){
  srand(time(NULL));
  int N=10; //zestawow dla 100000 kilka s, sprawdzaj z 10000
  int n, z;
  int a=500; //liczba elementow tablicy
  int b=500; //liczby nie wieksze niz 500

  //--------liczby losowe
  printf("%d\n",N);
  FOR(i,N){
    n=rand()%a+2; //liczb w tablicy
    printf("%d 1\n",n);
    FOR(j,n){
      z=rand()%b;
      printf("%d\n", z);
    }
  }

  //-------prawie posortowane rosnaco
  printf("%d\n",N);
  FOR(i,N){
    n=rand()%a+2; //liczb w tablicy
    printf("%d 1\n",n);
    int *tablica1 = (int *)malloc( n * sizeof(int));

    FOR(j,n){
      z+=rand()%b;
      tablica1[j]=z;
    }

    //prawie bo zamieniam 2 el miejscami
    swap(tablica1, 0, n/2);
    FOR(j,n){
      printf("%d\n", tablica1[j]);
    }
    free(tablica1);
  }

  //-------posortowane rosnaco
  z=0;
  printf("%d\n",N);
  FOR(i,N){
    n=rand()%a+2; //liczb w tablicy
    printf("%d 1\n",n);
    int *tablica1 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z+=rand()%b;
      z%=1000000;
      tablica1[j]=z;
      printf("%d\n",tablica1[j]);
    }
    free(tablica1);
  }

  //-------prawie posortowane malejaco
  printf("%d\n",N);
  z=500000+rand();
  FOR(i,N){
    n=rand()%a+2; //liczb w tablicy
    printf("%d\n 1",n);
    int *tablica1 = (int *)malloc( n * sizeof(int));
    FOR(j,n){
      z-=rand()%500;
      tablica1[j]=z;
    }
    //prawie bo zamieniam 2 el miejscami
    swap(tablica1, 0, n/2);
    FOR(j,n){
      printf("%d\n", tablica1[j]);
    }
    free(tablica1);
  }

  //--------posortowana malejaco
  z=500000+rand()%a;
  printf("%d\n 1",N);
  FOR(i,N){
    n=rand()%a+2; //liczb w tablicy
    printf("%d\n",n);
    z=500000+rand()%a;
    FOR(j,n){
      z-=rand()%500;
      printf("%d\n", z);
    }
  }
}
