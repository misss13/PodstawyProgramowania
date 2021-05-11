#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
  FILE *plik;

  for(int i=1; i<argc; i++){
    char ch;
      //zdanie[1000];

    plik=fopen(argv[i], "r");

    while((ch = fgetc(plik)) != EOF){
      if(ch=='<'){
        ch=fgetc(plik);

        if(ch=='p'){ //aka
          ch=fgetc(plik);
        while((ch = fgetc(plik)) != EOF){
          if(ch=='<'){
            ch=fgetc(plik);
              if(ch=='/'){
                ch=fgetc(plik);
                if(ch=='p'){
                  printf("\n\n");
                  break;
                }}}
          printf("%c", ch);
        }
        }
        if(ch=='t'){
          ch=fgetc(plik);
          if(ch=='a'){
            for(int j=0; j<5; j++)
              ch=fgetc(plik);
            while((ch = fgetc(plik)) != EOF){ //co w tabelce

              if(ch=='d'){ //td
                ch=fgetc(plik);
                if(ch=='>'){
                  while((ch = fgetc(plik)) != EOF){
                    if(ch=='<'){
                      printf("\t");
                      break;
                    }
                    printf("%c", ch);
                  }
                }
              }

              if(ch=='/'){// tr
                ch=fgetc(plik);
                if(ch=='t'){
                  ch=fgetc(plik);
                  if(ch=='r'){
                    printf("\n");
                  }
                }
              }

              if(ch=='e'){ //koniec
                ch=fgetc(plik);
                if(ch=='>')
                  break;
              }
              //printf("%c", ch); //debug
            }

          }
        }
      }
    }
    fclose(plik);
  }
}
