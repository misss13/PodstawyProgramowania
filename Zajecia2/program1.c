#define NN 21
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//nie definiuje tutaj tablic z prostego powodu ggdyż definiując je poza funkcja elementom tablicy przypisywana jest losowa wartość zalegająca w pamięci ram i pouczano mnie niejednokrotnie by nie definiowac w tym miejscu tablic

void printab3(int t3[], int n3)
{
  for(int i=0; i<n3; i++)
    printf("tab3[%d] = %d\n", i, t3[i]);
  printf("\n");
}
void printab(int t1[], int n1, int t2[], int n2)
{
  for(int i=0; i<n1; i++)
    printf("tab1[%d] = %d\n", i, t1[i]);
  printf("\n");
  for(int i=0; i<n2; i++)
    printf("tab2[%d] = %d\n", i, t2[i]);
  printf("\n");
}

void reverse(int tablice[], int N)
{
  int ta[N];
  for(int i=0; i<N; i++)
    ta[i]=tablice[i];
  int j=0;
  for(int i=--N; i>=0; i--)
    {
      tablice[j]=ta[i];
      j++;
    }
}

void sortowanie(int tab[], int n)
{
  int k;
  for(int i=0; i<n; i++)
    for(int j=0; j<(n-1); j++)
      if (tab[j] > tab[j + 1])
      {
        k= tab[j];
        tab[j]=tab[j+1];
        tab[j+1]=k;
      }
}

int one_two(int t1[], int n1, int t2[], int n2, int t3[])
{
  int n3=n1+n2;
  int p,temp; //pomocnicze
  int  t[n3];

  p=0;
  for(int i=0; i<n3; i++) //sumuje tablice
  {
    if(i<n1)
    {
      t3[i]=t1[i];
    }
    else
    {
      t3[i]=t2[p];
      p++;
    }
  }

  sortowanie(t3,n3); //sortuje
  printf("-----przed wyrzuceniem powtorzen-----\n");
  printab3(t3, n3);

  //wyrzucam powtorzenia zwracam dl t3 bez powtorzen
  for(int i=0; i<n3 ;i++)
    t[i]=t3[i];
  temp=-10;
  p=0;

  for(int i=0; i<n3; i++)
  {
    if(t[i]!=temp)
    {
      t3[p]=t[i];
      p++;
      temp=t[i];
    }
  }
  return p;
}

void statystyka(int T[], int wyn[])
{
  int znak; //true/false ?-1true : 1false
  double proc = 0.0;

  for(int i=0; i<NN; i++) //jednak moja teoria sie nie sprawdzila :<
    wyn[i]=0;

  for(int i=0; i<NN; i++)
  {
    znak = (rand()%2) ? -1 : 1;
    T[i]=rand()%11;
    T[i]*=znak;
    (wyn[(T[i]+10)])++;
    printf("T[%d] = %d\n", i, T[i]);
  }
  printf("liczba <=> stat_proc");
  for(int i=0; i<NN; i++)
  {
    proc = 100.0 * wyn[i]/NN;
    printf("%d <=> %lf %%\n", i-10, proc);
  }
}

int main(void)
{
  srand(time(NULL));

  int N1, N2, N3;
  scanf("%d", &N1);
  scanf("%d", &N2);
  int t1[N1];
  int t2[N2];
  int t3[N1+N2];
  int T[NN];
  int wyn[21];

  for(int i=0; i<N1; i++)
  {
    t1[i]=rand();
    t1[i]=(t1[i]%10)+1;
  }

  for(int i=0; i<N2; i++)
  {
    t2[i]=rand();
    t2[i]=(t2[i]%10)+1;
  }

  printf("-----tablice wylosowane-----\n");
  printab(t1, N1, t2, N2);
  printf("-----tablice odwrocone------\n");
  reverse(t1, N1);
  reverse(t2, N2);
  printab(t1, N1, t2, N2);
  printf("-----tablice posortowane----\n");
  sortowanie(t1, N1); //babelkowe
  sortowanie(t2, N2);
  printab(t1, N1, t2, N2);
  printf("-----tablice dodane bez pow-\n");
  N3=one_two(t1, N1, t2, N2, t3);
  printf("--ostatecznie--\n");
  printab3(t3, N3);
  printf("-----statystyka-------------\n");
  statystyka(T, wyn);
}
