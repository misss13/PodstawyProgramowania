#define FOR(i,n) for(int i = 0; i<n ;i++)
#include <stdio.h>
#include <string.h>

int Gupi_s(char slowo[], int dl)
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
    if(s==1 && slowo[i]!=' ' && slowo[i+1]==' ')
    {
      k=1;
      break;
    }
    if(slowo[i]!=' ' && s==1)
      l+=1;
  }

  return l;
}

void FyszrCezara(char slowo[], int dl)
{
  int s = Gupi_s(slowo, dl);
  FOR(i,dl)
  {
    if(slowo[i]>='a' && slowo[i]<='z')
      slowo[i]='a'+(slowo[i]+s-'a')%26;
    if(slowo[i]>='A' && slowo[i]<='Z')
      slowo[i]= 'A'+(slowo[i]+s-'A')%26;
  }
  printf("%s\n", slowo);
}

int main(void)
{
  //char slowo[]="Ala ma kota";
  // char slowo[]="to";
  char slowo[]="  Alaa ma kota";
  int d = strlen(slowo);
  FyszrCezara(slowo, d);
  return 0;
}
