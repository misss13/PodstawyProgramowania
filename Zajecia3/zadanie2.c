#define FOR(i,n) for(int i = 0; i<n ;i++)
#define duzo 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Gupi_s(char slowo[], int dl) //odpowiada za przesuniecie
{
  int s=0;
  int k=0;
  int l=0;

  FOR(i,dl)
    {
      if(slowo[i]!=' ' && s==0)
        {
          s=1;
          l+=1;
        }
      if(s==1 && slowo[i]!=' ' && (slowo[i+1]==' ' || i+1==dl))
        {
          k=1;
          break;
        }
      if(slowo[i]!=' ' && s==1)
        l+=1;
    }

  return l;
}

void FyszrCezara(char slowo[], int dl) //szyfruje
{
  int s = Gupi_s(slowo, dl);
  FOR(i,dl)
    {
      if(slowo[i]>='a' && slowo[i]<='z')
        slowo[i]='a'+((slowo[i]+s-'a')%26);
      if(slowo[i]>='A' && slowo[i]<='Z')
        slowo[i]= 'A'+((slowo[i]+s-'A')%26);
    }
}

char* getEncryptedLine()
{
  int d=(-1);
  char *slowo = malloc(duzo * sizeof(char));

  if (fgets(slowo, duzo, stdin) == NULL)
  {
    free(slowo);
    return NULL;
  }

  slowo[strcspn(slowo, "\n")] = 0; //koniec lini koniec slowa biore dlugosc
  d = strlen(slowo);

  if(d>=1)
  {
    FyszrCezara(slowo, d);
    return slowo;
  }
  else
  {
    free(slowo);
    return NULL;
  }
}

int main(void)
{
  while(1)
  {
  char *slowo = getEncryptedLine();
  if(slowo==NULL)
  {
    free(slowo);
    break;
  }

  printf("%s\n", slowo);
  free(slowo);

  }
  return 0;
}
