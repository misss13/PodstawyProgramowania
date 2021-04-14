#define FOR(i,n) for(int i=0; i<n; i++)
#define duzo 100

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char* getHexAscii(char znak)
{
  char *hexa = (char*) malloc(2*sizeof(char));
  sprintf(hexa, "%x", znak);
  return hexa;
}

char** getData(int *count)
{
  int w=3;
  char **macierz = (char **) malloc(3*sizeof(char *));
  FOR(i,3)
    {
      macierz[i] = (char *) malloc(duzo * sizeof(char));
      *macierz[i]='\0';
    }
  FOR(i,3)
    {
      (*count)++;
      if (fgets(macierz[i], duzo, stdin) == NULL || strcmp(macierz[i], "\n") == 0)
        {
          w=0;
          for(int j=i; j<3; j++)
            {
              *macierz[j]='\0'; //macierz[j]=NULL nie ma sensu bo uzywamy miejsca w pamięci 0x0 do którego nie mam prawa CO NIE MA SENSU valgrind ma z tym rowniez problem rozumiem ze zawartość ma być NULL czyli w tym wypadku '\0' a przynajmniej tak napisane jest w internecie na stackoverflow ('\0'kazdy string sie tym konczy)
            }
          break;
        }
      if(w)
        printf("%s",macierz[i]); //mozna zakomentowac zeby nie wypisywal nic
    }

  while(w>0)
    {
      (*count)++;
      macierz= (char **) realloc(macierz,(w+1)*sizeof(char *));
      macierz[w]= (char *) malloc(duzo*sizeof(char));
      *macierz[w]='\0';
      if (fgets(macierz[w], duzo, stdin) == NULL || strcmp(macierz[w], "\n") == 0)
        {
          macierz= (char **) realloc(macierz,(w)*sizeof(char *));
          w=0;
          (*count)--;
          break;
        }
      printf("%s", macierz[w]);
      w+=1;
    }
  return macierz;
}

char *compress(char **tekst, int size)
{
  int wiersz=size;
  char *wynik= (char *) malloc(duzo*sizeof(char));
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
          else
            {
            if (counter > 4 || c == '%' || c == '(' || c == ')')
              {
                if(c == '%' || c == '(' || c == ')')
                {
                  wynik[out] = '%';
                  wynik[out+1]=getHexAscii(c)[0];
                  wynik[out+2]=getHexAscii(c)[1];
                  out+=3;
                }
              else
                {
                  wynik[out] = c;
                  out++;
                }
              wynik[out] = '(';
              out++;
              if (counter / 10)
                {
                  wynik[out] = '0' + (counter / 10);
                  out++;
                }
              wynik[out] = '0' + (counter % 10);
              out++;
              wynik[out] = ')';
              out++;
              }
            else
              {
              for (int j = 0; (j < counter && out < in); ++j)
                {
                  wynik[out] = linijka[in - 1];
                  out++;
                }
              }
            c = linijka[in];
            counter = 1;
            if ((linijka[in]) == '\n')
            {
              eof=1;
              wynik[out]='\n';
              out++;
            }
          }
        }

      for(int it = out; it < duzo; it++)
        {
        wynik[it] = 0;
        }
    }
  return wynik;
}


char* decompress(char** tekst, int size)
{
  int wiersz=size;
  char *wynik=(char *) malloc(duzo*sizeof(char));
  char first = 0;
  char second = 0;
  int out = 0;
  int counter = 0;
  FOR(k,wiersz)
    {
    char *linijka=tekst[k];
    FOR(i,duzo)
      {
        first = linijka[i];
        if(first == '%')
          {
            if(linijka[i+2] == '5')
                first = '%';
            if(linijka[i+2] == '8')
                first = '(';
            if(linijka[i+2] == '9')
                first = ')';
            i += 4;
            if(linijka[i+1] != ')')
              {
                counter = (10 * (linijka[i] - '0')) + (linijka[i+1] - '0');
                i += 2;
              }
            else{
                counter = (linijka[i] - '0');
                i++;
            }
          }
      else if(linijka[i+1] == '(')
        {
          i=i+2;
          if(linijka[i+1] != ')')
          {
            counter = (10 * (linijka[i] - '0')) + (linijka[i+1] - '0');
            i+=2;
          }
          else
            {
                counter = (linijka[i] - '0');
                i++;
            }
          }
      else if(linijka[i]=='\n')
        {
          wynik[out]='\n';
          out++;
          first=0;
          second=0;
          counter=0;
          break;
        }
      else
        counter = 1;
      FOR(j,counter)
      {
        wynik[out] = first;
        out++;
      }

      }
    }

 return wynik;
}



int main(int argc, char **argv)
{
  int *wiersze =(int *) malloc(sizeof(int));
  (*wiersze)=0;
  //------compress-----------
  if((argc == 1) || ((strcmp(argv[1], "--compress"))==0))
    {
      char **tekst=getData(wiersze);
      int temp=*wiersze;
      char *komp=compress(tekst, temp);
      printf("%s\n", komp);

      //---free----
      FOR(i,*wiersze)
        free(tekst[i]);
      free(tekst);
      free(komp);
    }
  //-------decompress--------
  else if((strcmp(argv[1], "--decompress")==0))
    {
      char **tekst1=getData(wiersze);
      int temp1=*wiersze;
      char *deko=decompress(tekst1, temp1);
      printf("%s\n", deko);

      //----free----
      FOR(i,*wiersze)
        free(tekst1[i]);
      free(tekst1);
      free(deko);
    }
  else
    printf("Nieprawidlowy format!!!\n");

  //---free----
  free(wiersze);
}
