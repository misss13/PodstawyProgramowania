#define mak 15

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void podciag(int t[])
{
  int mk,mp,dm,di,i; //aktualne a, maksymalny koniec, maksymalny poczatek
  double a, aa,ak;
  dm=-10;
  aa= (double) t[1]/t[0];
  ak=0;
  di=1;
  for(i=0;i<mak-1;i++)
  {
    ak=(double) (t[i+1]/t[i]);
    //printf("%f",t[i+1]);
    if(ak==aa){
      di+=1;
    }
    else
      {
        if(di>dm)
          {
            dm=di;
            mp=i-dm+1;
            mk=i;
          }
        di=2;
        aa=(double)t[i+1]/t[i];
      }
  }
  if(di>dm)
    {
       dm=di;
       mp=i-dm+1;
       mk=i;
     }
  if(dm>2)
    {
      printf("\n");
      for(int i=mp; i< mk; i++)
        printf(" %d ", t[i]);
      printf("\nIndex pierwszy: %d\nIndex ostatni %d\n", mp, mk);
    }
}

int main(void)
{
  srand(time(NULL));

  int t[mak];

  for(int i=0;i<mak;i++)
  {
    t[i]=rand();
    t[i]=(t[i]%10)+1;
    printf(" %d ", t[i]);
  }
  printf("");

  //znajdowanie podciagu geometrycznego
  podciag(t);

}
