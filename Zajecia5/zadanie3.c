#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int wez(FILE *a, int index){
  fseek(a, 4, SEEK_SET);
  int b;
  for (int i = 0; i <= index; i++)
    fscanf(a, "%d", &b);
  return b;
}

void mnozenie(FILE* a, FILE* b, FILE*c, int w1, int k1w2, int k2){
  int z1, z2, s=0, i,j,k;
  fprintf(c, "%d %d\n", w1, k2);

  //-----------operacje w pam 2 elementy-----
  for (i = 0; i < w1; i++) {
    for (j = 0; j < k2; j++) {
      s = 0;
      for (k = 0; k < k1w2; k++){
        s += wez(a, i * k1w2 + k) * wez(b, j + k2 * k);
      }
      fprintf(c, "%d\t", s);
    }
    fprintf(c, "\n");
  }
}
  //-----------koniec -----------------------

int main(int argc, char *argv[]){
  if(argc>2 || argc<2){
    printf("zla skladnia!\nzadanie3 [lista]\n");
    exit(-1);
  }
  else{
    FILE *lista;
    if((lista=fopen(argv[1],"r"))==NULL)
      return -1;

    int licz=0;
    char plik1[10], plik2[10], plik3[10];
    char pomo;

    for (pomo = getc(lista); pomo != EOF; pomo = getc(lista))
      if (pomo == '\n')
        licz+=1;

    fseek(lista,0,0);
    for(int i=0; i<licz; i++){

     fscanf(lista, "%s", plik1);
     fscanf(lista, "%s", plik2);
     fscanf(lista, "%s", plik3);

      FILE *macierz1,
           *macierz2,
           *macierz3;

      if((macierz1=fopen(plik1,"r"))==NULL)
        return -1;
      if((macierz2=fopen(plik2,"r"))==NULL)
        return -1;
      if((macierz3=fopen(plik3,"w"))==NULL)
        return -1;
      int w1,
        k1w2,
        k2;
      fscanf(macierz1,"%d %d\n",&w1, &k1w2);
      fscanf(macierz2,"%d %d\n",&k1w2, &k2);

      mnozenie(macierz1, macierz2, macierz3, w1, k1w2, k2);

      fclose(macierz1);
      fclose(macierz2);
      fclose(macierz3);
      }
  fclose(lista);
  }
}
