#define DLU 8
#define FOR(i,n) for(int i=0; i<n; i++)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void losuj(int t[DLU][DLU])
{
  FOR(i,DLU)
    FOR(j,DLU)
    t[i][j]=rand()%10;
}

void printab(int t[DLU][DLU])
{
  FOR(i,DLU)
    {
    FOR(j,DLU)
      printf(" %d ",t[i][j]);
    printf("\n");
    }
}

void sumy(int t[DLU][DLU])
{
  int sum;
  //przekatne suma
  sum = 0;
	FOR(i,DLU)
    sum += t[i][i];
	printf("Suma na przekątnej %d\n", sum);

  //kolumny suma
  printf("Suma kolumn\n");
  FOR(i,DLU)
  {
    sum=0;
    FOR(j,DLU)
      sum+=t[j][i];
    printf(" %d ", sum);
  }
  printf("\n");

  //wszystkie suma
  sum=0;
  FOR(i,DLU)
    FOR(j,DLU)
     sum+=t[i][j];
  printf("Suma wszystkich el %d\n", sum);

}

void mnozenie(int t1[DLU][DLU], int t2[DLU][DLU])
{
  int p=0;
  FOR(i,DLU)
  {
    FOR(j,DLU)
    {
      p=0;
      FOR(k,DLU)
        p+=t1[i][k]*t2[k][j];
      printf("%d\t", p);
    }
    printf("\n");
  }
}

int main(void)
{
  srand(time(NULL));
  int t1[DLU][DLU];
  int t2[DLU][DLU];
  losuj(t1);
  losuj(t2);
  printf("-------losowanie-------\n");
  printab(t1);
  printf("\n");
  printab(t2);
  printf("-------Sumy 1----------\n");
  sumy(t1);
  printf("-------Sumy 2----------\n");
  sumy(t2);
  printf("----mnozenie t1 * t2---\n");
  mnozenie(t1, t2);
}
