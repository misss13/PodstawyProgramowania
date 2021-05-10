#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generuj(FILE *a, int w, int k){
  fprintf(a, "%d %d\n", w, k);
  for(int i=0; i<w; i++){
    for(int j=0; j<k; j++)
      fprintf(a, "%d ",rand()%100);
  fprintf(a,"\n");
  }
}

int main(int argc, char **argv){
  srand(time(NULL));
  if(argc<3 || argc>3){
    printf("poprawna skladnia:\n zadanie2.2 [min] [max]");
    exit(-1);
  }
  else{
  int w1,
      k2,
    k1w2;
  FILE *macierz1,
       *macierz2;
  int min=atoi(argv[1]);
  int max=atoi(argv[2]);

  w1=rand()%(max-min+1) + min;
  k2=rand()%(max-min+1) + min;
  k1w2=rand()%(max-min+1) + min;

  macierz1=fopen("macierz1", "w");
  macierz2=fopen("macierz2", "w");

  generuj(macierz1, w1, k1w2);
  generuj(macierz2, k1w2, k2);
  }
}
