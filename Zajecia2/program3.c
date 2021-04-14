#define FOR(i,n) for(int i=0; i<n; i++)

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int n;
  int p=1;

  scanf("%d", &n);
  int *macierz = (int *) malloc(n*n*sizeof(int));

  //int **macierz;
  // macierz = malloc(n * n * sizeof(int *)* sizeof(int));

  FOR(i,n)
    FOR(j,n)
    scanf("%d", (macierz + (n*i) + j));

  //wypisanie
  FOR(i,n)
  {
    FOR(j,n)
      printf("%d\t", *(macierz + (n*i) +j));
    printf("\n");
  }
  if(n==1)
    {
      printf("Za mała macierz\n");
      return 0;
    }


  FOR(i,n)
  {
    if(p==0)
      break;
		for(int j=(n-1); j>i ; --j)
    {
      if(p==0)
        break;
			if(*(macierz + (n*i) + j) != 0)
      {
				printf("To nie macierz trójkątna dolna\n");
				p=0;
			}
    }
  }

  if(p==1)
    printf("To macierz trójkątna dolna\n");

  free(macierz);
}

