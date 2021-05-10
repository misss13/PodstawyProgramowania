#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  if(argc != 4){
    printf("Zla skladnia!:\n zadanie2.3.c [macierz1] [macierz2] [macier3]\n");
    exit(-1);
  }
  else{
    FILE *macierz1,
      *macierz2,
      *macierz3;

    int k1w2,
      w1,
      k2,
      w3,
      k3,
      oo,
      pom=1,
      fail=0;

    if((macierz1=fopen(argv[1],"r"))==NULL)
      return -1;
    if((macierz2=fopen(argv[2],"r"))==NULL)
      return -1;
    if((macierz3=fopen(argv[3],"r"))==NULL)
      return -1;

    fscanf(macierz1,"%d %d\n",&w1, &k1w2);
    fscanf(macierz2,"%d %d\n",&k1w2, &k2);
    fscanf(macierz3,"%d %d\n",&w3, &k3);

    if(w3==w1 && k2==k3){
      printf("rozmiary macierzy: poprawne\n");
      fail=1;
    }
    else{
      printf("FAIL --rozmiary macierzy: nie poprawne\n");
    }

    int a[w1][k1w2];
    int b[k1w2][k2];
    int c[w1][k2];

    for (int i = 0; i < w1; i++){
      for(int j=0; j<k1w2; j++){
        fscanf(macierz1, "%d", &a[i][j]);
      }
    }

    for (int i = 0; i < k1w2; i++)
      for(int j=0; j<k2; j++)
        fscanf(macierz2, "%d", &b[i][j]);

    for (int i = 0; i < w1; i++)
      for(int j=0; j<k2; j++)
        fscanf(macierz3, "%d", &c[i][j]);

    int p=1;
    long int s=0;

    for(int i=0; i<w1; i++){
      for(int j=0; j<k2; j++){
        s=0;
        for(int k=0; k<k1w2; k++){
          s+=a[i][k]*b[k][j];
        }
        if(c[i][j]!=s){
          printf("Uwaga błędny element macierzy c! w c[%d][%d]=%d powinno byc %ld\n",i,j,c[i][j],s);
          pom=0;
        }
      }
    }

    if(pom==1 && fail==1){
      printf("--------------------SUCCESS------------------\n");
    }
    else{
      printf("---------------------FAIL--------------------\n");
    }
  }
}
