#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} Day;
typedef enum {DAY_EARLIER, DAY_LATER, TIME_EARLIER, TIME_LATER} Action;

int dl=0;

char* Day__toString(Day day){
  if(day==0)
    return "Poniedziałek";
  if(day==1)
    return "Wtorek";
  if(day==2)
    return "Środa";
  if(day==3)
    return "Czwartek";
  if(day==4)
    return "Piątek";
  if(day==5)
    return "Sobota";
  if(day==6)
    return "Niedziela";
}

Day Obsluga__Dni(char *s){
  if(!strcmp(s,"Mon"))
    return MON;
  if(!strcmp(s,"Tue"))
    return TUE;
  if(!strcmp(s,"Wed"))
    return WED;
  if(!strcmp(s,"Fri"))
    return FRI;
  if(!strcmp(s,"Sat"))
    return SAT;
  if(!strcmp(s,"Sun"))
    return SUN;
  if(!strcmp(s,"Thu"))
    return THU;
}

Day Day__nextDay(Day day){
  if(day==SUN)
    return MON;
  else
    return day+1;
}

Day Day__prevDay(Day day){
  if(day==MON)
    return SUN;
  else
    return day-1;
}

Action* parse(int rozmiarTablicy, char *tablica[]){
  int j=0;
  Action *zwrot = malloc(rozmiarTablicy * sizeof(*zwrot));
  for(int i=0; i<rozmiarTablicy-1; i++){
    if(!strcmp(tablica[i], "d-")){
      zwrot[j] = DAY_EARLIER;
      j++;
    }
    if(!strcmp(tablica[i], "d+")){
      zwrot[j] = DAY_LATER;
      j++;
    }
    if(!strcmp(tablica[i], "t-")){
      zwrot[j] = TIME_EARLIER;
      j++;
    }
    if(!strcmp(tablica[i], "t+")){
      zwrot[j] = TIME_LATER;
      j++;
    }
  }
  dl=j; //globalna dlugosc
  return zwrot;
}

int main(int argc, char **argv){
  int dlugosc=argc-1;

  if(argc < 2){
    printf("Zła składnia!\nzadanie1 [dzien_tyg] [opcje po spacji]\n");
    return 1;
  }

  Day day=Obsluga__Dni(argv[1]);
  argv+=2; //zaczynamy od opcji
  Action *pokolei=parse(dlugosc, argv);

  for(int i=0; i<dl; i++){
    //printf("%d",pokolei[i]);//debug
    switch(pokolei[i])
      {
      case DAY_EARLIER:
        printf("Dzień w tył\n");
        day=Day__prevDay(day);
        break;
      case DAY_LATER:
        printf("Dzień w przód\n");
        day=Day__nextDay(day);
        break;
      case TIME_LATER:
        printf("Termin w przód\n");
        break;
      case TIME_EARLIER:
        printf("Termin w tył\n");
        break;
      default:
        printf("");
      }
  }
  printf("Wynik przesunięcia: \"%s\"\n", Day__toString(day));
  return 0;
}
