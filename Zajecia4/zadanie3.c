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

int maax(int *arr, int n){
  int x = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > x)
      x = arr[i];
  return x;
}

void countSort(int arr[], int n, int exp)
{
  int output[n];
  int i, count[10]={0};

  for (i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  for (i = 1; i < 10; i++)
    count[i] += count[i - 1];
  for (i = n - 1; i >= 0; i--){
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }
  FOR(i,n)
    arr[i] = output[i];
}

void radixsort(int *arr, int n){
  int m = maax(arr, n);
  for (int exp = 1; m / exp > 0; exp *= 10)
    countSort(arr, n, exp);
}

int main(void){

  //-----wczytywanie testu
  int n,z,c;

  scanf("%d", &z);
    FOR(i,z){
      scanf("%d %d",&n, &c);
      int *tablica = (int *)malloc( n * sizeof(int));

      FOR(j,n)
        scanf("%d", &tablica[j]);
      //printf("%d\n", tablica[j]); //debug DLA MALYCH TESTOW
      //radix

      radixsort(tablica, n);
      print(tablica, n);

      //free
      free(tablica);
    }
}
