#include <time.h>
#include <stdio.h>
#include <math.h>

int nwd(int a, int b){
  return (a==0) ? b : nwd(b%a,a);
}

int wzgledni(int a, int b){
  return(nwd(a ,b)==1);
}

int main(void){
  srand(time(NULL));
  double c,d;
  int a;
  int w=0;
  int b;
  int N=100000000;
  for(int i=0; i<N; i++){
    a=rand();
    b=rand();
    if(wzgledni(a ,b)==1)
      w+=1;
  }
  d=(double) (6*N/w);
  c=sqrt(d);
  printf("pi = %f\n", c);
}
