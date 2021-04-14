#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** getData(int *count)
{
  int w=0;
  char **macierz = (char **) malloc(3*sizeof(char *));
  while(w>-1)
    {
      (*count)++;
      macierz= (char **) realloc(macierz,(w+1)*sizeof(char *));
      macierz[w]= (char *) malloc(duzo*sizeof(char));
      *macierz[w]='\0';
      if (fgets(macierz[w], duzo, stdin) == NULL || strcmp(macierz[w], "\n") == 0)
        {
          macierz= (char **) realloc(macierz,(w)*sizeof(char *));
          w=(-1);
          (*count)--;
          break;
        }
      //printf("%s", macierz[w]);
      w+=1;
    }
  return macierz;
}

void funkcja(char **tekst, int wiersze)
{
  int litery=0;
  int sumacyfr=0;
  char c=0;
  int d=0;
  int x;
  int pocz;
  int kon;
  int liczba=0;
  int sumaglob=0;
  int sumalicz=0;
  int pom=0;
  printf("Napis Sumac\tIloscl\tSumal\n");
  FOR(i,wiersze)
    {
      char *linijka=tekst[i];
      d = strlen(linijka); 
      char *kopia=(char*)malloc(d*sizeof(char));
      strcpy(kopia,linijka);
      litery=0;
      pocz=0;
      kon=0;
      pom=0;
      sumacyfr=0;
      linijka[strcspn(linijka, "\n")] = 0;
      FOR(j,d)
        {
          c=linijka[j];
          if((c>='A'&&c<='Z')||(c>='a'&&c<='z'))
            {
              litery+=1;
              kon=1;
            }
          else if(c>='0'&&c<='9')
            {
              x=(int) (c-'0');
              sumacyfr+=x;
              if(j==0)
                pocz=1;
              if(pocz==1 && kon==0)
                pom+=1;
            }
           }
      kopia[pom]='\n';
      kopia[strcspn(kopia, "\n")] = 0;
      sumalicz=atoi(kopia);
      sumaglob+=sumalicz;
      // FOR(k,d)
      //printf("%c",tekst[i][k]);
      printf("%s\t%d\t%d\t%d\n",tekst[i], sumacyfr, litery, sumaglob);
    }

}

int main(void)
{
  int *wiersze = (int *) malloc(sizeof(int));
  (*wiersze)=0;
  char **tekst=getData(wiersze);
  int temp=*wiersze;
  funkcja(tekst, temp);

  //free
  FOR(i, *wiersze)
    free(tekst[i]);
  free(tekst);
  free(wiersze);
}
