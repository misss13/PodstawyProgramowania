#define FOR(i,n) for(int i=0; i<n; i++)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  srand(time(NULL));
	int k,w;
  printf("Prosze podać ilość kolumn: \n");
  scanf("%d", &k);
  printf("Proszę podać ilość wierszy: \n");
  scanf("%d", &w);

	int **macierz = (int **)malloc(w * sizeof(int *)); //u mnie int* ma 8B
	FOR(i,w)
		macierz[i] = (int *)malloc(k * sizeof(int)); //int 4B

	// macierz[i][j] to *(*(macierz+i)+j)
	FOR(i,w)
    FOR(j,k)
      *(*(macierz+i)+j) = rand()%100;

  printf("-------macierz---------\n");
	FOR(i,w)
  {
    FOR(j,k)
      printf("%d\t ", *(*(macierz+i)+j));
    printf("\n");
  }

  //sprzatanie
  FOR(i,w)
    free(macierz[i]);
  free(macierz);
  return 0;
}
