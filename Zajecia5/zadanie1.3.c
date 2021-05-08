#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void printi(int arr[], int elem){
  for(int i=0; i<elem; i++)
    printf("%d ", arr[i]);
  printf("\n");
}

void printc(char arr[], int elem){
  for(int i =0;i<elem; i++)
    printf("%c ", arr[i]);
  printf("\n");
}

void sortowanie(int arri[], char arrc[], int elem, char typ, FILE* a){
  int mini;
  int akt,
      kubek,
      akt_mini;
  if(typ=='c'){ //zamiana na liczby
    for(int i=0; i<elem; i++)
      arri[i]=(int) arrc[i];
    fwrite(arri, sizeof(int), elem, a);
  } //--uwaga sam algorytm bd wykonywany na 2 variabl--

  for(int i=0; i<elem-1; i++){
    mini=i;
    for(int j=i+1; j<elem; j++){
      fseek(a, j*sizeof(int), 0);
      akt=getc(a); //pierwszy element
      fseek(a, mini*sizeof(int), 0);
      akt_mini=getc(a); //drugi element
      if(akt<akt_mini)
        mini=j;
    }
    fseek(a, i*sizeof(int), 0);
    akt=getc(a);
    fseek(a, mini*sizeof(int), 0);
    akt_mini=getc(a);
    kubek=akt_mini; //uzywam do zamiany elementow!
    fseek(a, mini*sizeof(int),0);
    putc(akt, a);
    fseek(a, i*sizeof(int), 0);
    putc(kubek, a);
  }//--------koniec 2 zmiennych------

  fseek(a,0,0);
  fread(arri, sizeof(int), elem, a);

  if(typ=='c'){
    for(int i=0; i<elem; i++)
      arrc[i]=(char) arri[i];
    fseek(a,0,0);
    fwrite(arrc, sizeof(char), elem, a);
    printc(arrc, elem);
  }
}

void generuj(int elem, char typ, FILE* a, int arri[], char arrc[]){
  int los;
  for(int i=0; i<elem; i++){
    if(typ=='c'){
      los=(rand()%(58))+65; //122-65+1=57+1=58
      arrc[i]=(char)los;
    }
    if(typ=='i'){
      los=rand()%100; //mozna zmienic na wieksze war
      arri[i]=los;
    }
  }
  if(typ=='i'){
    fwrite(arri, sizeof(int), elem, a);
    //printi(arri, elem);
  }
  if(typ=='c'){
    fwrite(arrc, sizeof(char), elem, a);
    //printc(arrc, elem);
  }
}

void list(FILE* a, int arri[], char arrc[], int typ, int elem, int state){
  int lit;
  if(typ=='c'){
    fread(arrc, sizeof(char), elem, a);
    if(state==1)
      printc(arrc, elem);
  }
  if(typ=='i'){
    fread(arri, sizeof(int), elem, a);
    if(state==1)
      printi(arri, elem);
  }
}

int main(int argc, char *argv[]){
  srand(time(NULL));

  if(argc != 5){
    printf("Zla skladnia!\nzadanie1 [nazwa pliku] [liczba el] [c-char/i-int] [-ARG]\nDostepne ARG\n-g  generuj\n-s  sortuj\n-l  wypisanie elementow\n");
    return 1;
  }

  else{
    int elementy=atoi(argv[2]);
    char typ=argv[3][0];
    FILE* pliczek;
    int arri[elementy];
    char arrc[elementy];

    if(strcmp(argv[4], "-g")==0){
      pliczek = fopen(argv[1], "wb");
      generuj(elementy,typ, pliczek, arri, arrc);
      fclose(pliczek);
    }

    if(strcmp(argv[4], "-s")==0){
      if((pliczek = fopen(argv[1], "rb"))==NULL)
        return -1; //zwraca blad
      list(pliczek, arri, arrc, typ ,elementy, 0);
      fclose(pliczek);
      pliczek=fopen(argv[1], "r+b");
      sortowanie(arri, arrc, elementy, typ, pliczek);
      fclose(pliczek);
   }

    if(strcmp(argv[4], "-l")==0){
      if((pliczek = fopen(argv[1], "rb"))==NULL)
        return -1;
      list(pliczek, arri, arrc, typ, elementy, 1);
      fclose(pliczek);
    }
  }
  return 0;
}
