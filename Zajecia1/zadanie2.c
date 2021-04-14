#include <stdio.h>
#include <math.h>

int main(void)
{
  srand(time(NULL));

  int N;
  int a, b, c;
  double delta, x1, x2;

  N=rand();
  N%=10;
  N++;
  for(int i=0; i<N;i++)
    {
      printf("Rownanie nr %d\n", i);
      a=rand();
      b=rand();
      c=rand();
      a%=100; //zeby były male liczby
      b%=100;
      c%=100;
      a++;
      b++;
      c++;
      printf("%d x^2 + %d x + %d\n", a, b, c);
      delta=(double) (b*b)-(4*a*c);
      if(a==0) //jak usune a++
        {
          a=(-c)/b;
          printf("x= %d\n", a);
        }

      if(a==0 && b==0)
        printf("sprzecznosc!\n");

      if(delta>0.0)
        {
          x1=(double) ((-b)-sqrt(delta))/(2.0*a);
          x2=(double) ((-b)+sqrt(delta))/(2.0*a);
          printf("pierwiastek 1: %f\npierwiastek 2: %f\n", x1, x2);
        }

      if(delta==0.0)
        {
          x1=(double) ((-b)/(2.0*a));
          printf("pierwiastek : %f\n", x1);
        }

      if(delta<0.0)
        {
          x1=(double) ((-b)/(2.0*a));
          x2=(double) (sqrt(-delta))/(2*a);
          printf("pierwiastek 1: %f + %fi\npierwiastek 2: %f - %fi\n", x1, x2, x1, x2);
        }
  }
  //==debugowanie==
  // printf("\n%f\n", delta);
  // double aa=delta;
  // aa=sqrt(-aa);
  // printf("%f\n", aa);
  // return 0;
}
