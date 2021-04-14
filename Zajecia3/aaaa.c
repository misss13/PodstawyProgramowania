#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 100
#define LINE_LENGTH 100
#define DEFAULT_SIZE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* getHexAscii(char znak)
{
  char *hexa = malloc(2*sizeof(char));
  sprintf(hexa, "%x", znak);
  return hexa;
}

char** getData(void)
{
  int w=3;
  char **macierz =malloc(3*sizeof(char *));
  FOR(i,3)
  {
    macierz[i] = malloc(duzo * sizeof(char));
    macierz[i]=NULL;
  }
  FOR(i,3)
  {
    if (fgets(macierz[i], duzo, stdin) == NULL || strcmp(macierz[i], "\n") == 0)
      {
        //printf("KUPA");
        macierz[i]=NULL;
        w=0;
        break;
      }
    printf("%s",macierz[i]);
  }

  while(w>0)
  {
    macierz=realloc(macierz,(w+1)*sizeof(char *));
    macierz[w]=malloc(duzo*sizeof(char));
    macierz[w]=NULL;
    if (fgets(macierz[w], duzo, stdin) == NULL || strcmp(macierz[w], "\n") == 0)
    {
      macierz=realloc(macierz,(w)*sizeof(char *));
      w=0;
      //printf("NIELUBIETEGOZADANIA");
      break;
    }
    printf("%s", macierz[w]);
    w+=1;
  }

  return macierz;
}

/*char* compress(char** tekst)
{
  char odp[duzo];
  int p=0;
  int l=0;
  int k=0;
  char akt;
  char hexa;
  int pom=0;
  int wiersz=sizeof(tekst)/sizeof(tekst[0]);

  FOR(i,wiersz)
  {
    char *linijka = tekst[i];
    int dl = strlen(linijka);

    akt=linijka[0];
    l=0;
    p=0;
    k=0;

    FOR(i,dl)
    {
      if 
      if(akt=='(')
      {
        hexa=getHexAscii(akt);
      }

    }
    free(linijka);
  }
  return "aaa";
  }*/
/*
char *compress(char **tekst)
{
  int wiersz=sizeof(tekst)/sizeof(tekst[0]);
  char *wynik=malloc(duzo*sizeof(char));
  char c = 0;
  int counter = 0;
  int out = 0;
  char eof = 0;
  FOR(i,wiersz)
  {
    eof=0;
    char *linijka=tekst[i];
    for(int in = 0; (in < duzo && !eof); ++in)
    {
      if(c == linijka[in])
        {
          counter++;
        }
      else {
        if (counter > 4 || c == '%' || c == '(' || c == ')') {
          if(c == '%' || c == '(' || c == ')'){
            wynik[out] = '%';
            wynik[out+1]=getHexAscii(c)[0];
            wynik[out+2]=getHexAscii(c)[1];
            out+=3;
          }
          else {
            wynik[out] = c;
            out++;
          }
          wynik[out] = '(';
          out++;
          if (counter / 10) {
            wynik[out] = '0' + (counter / 10);
            out++;
          }
          wynik[out] = '0' + (counter % 10);
          out++;
          wynik[out] = ')';
          out++;
        }
        else {
          for (int j = 0; (j < counter && out < in); ++j)
            {
              wynik[out] = linijka[(in - 1)];
              out++;
            }
        }
        c = linijka[in];
        counter = 1;
        if ((linijka[in]) == 0)
          eof = 1;
      }
    }

        //printf("OUT: %d \n", out);
    for(int it = out; it < duzo; it++) {
      wynik[it] = 0;
    }
    //free(linijka);
    // FOR(i,out+1)
    //  lnijka[i]=wynik[i];
    //strcpy(linijka, wynik);
  }
  return wynik;
}

*/
int main(void)
{
  //-------I.1-----
  char a='(';
  char *aa=getHexAscii(a);
  printf("%s\n", aa);
  //--------I.2------
  char **aaa=getData();
  int gupiwiersz=sizeof(aaa) / sizeof(aaa[0]);
  //---------3---------
  //char *aaaa=compress(aaa);
  //  compress1(&(data[i]));
  //char b[2];
  //printf("%d",asciiToHex('(',b,0));
  //char *b = compress(aaa);
  //printf("%s",b);
    //FOR(i,gupiwiersz)
    //    compress1(&(aaa[i]));
    //FOR(i,gupiwiersz)
    //printf("%s\n", aaa[i]);
  //----strefa-freee----
  free(aa);
  //free(b);
  FOR(i,gupiwiersz)
    free(aaa[i]);
  free(aaa);
}
