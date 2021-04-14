#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  srand(time(NULL));
  //uzywam obecnego czasu jako seed do generowania losowej liczby
  int N;
  int a=-1;
  int liczba_prob=0;

  N=rand();
  N=(N%100)+1;
  //printf("%d\n", N);
  while(1)
  {
    scanf("%d", &a);
    if(a<N)
      printf("Wylosowana liczba jest większa, zgaduj dalej \n");
    if(a>N)
      printf("Wylosowa liczba jest mniejsza, zgaduj dalej \n");
    if(a==N)
      {
        printf("Brawo, zgadłeś liczbę po %d próbach\n", liczba_prob);
        break;
      }
    liczba_prob++;
  }
}
