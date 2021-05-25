#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <CUnit/Basic.h>


int dl;

typedef enum {FORWARD, BACKWARD, RIGHT, LEFT} MoveDirection;
typedef enum {NORTH, SOUTH, WEST, EAST} MapDirection;

typedef struct{
  int x;
  int y;
} Vector2d;

typedef struct{
  MapDirection orientation;
  Vector2d* position;
} Animal;

Vector2d* Vector2d__create(int x, int y){
  Vector2d* vec=malloc(sizeof(Vector2d));
  vec->x=x;
  vec->y=y;
}

void Vector2d__toString(Vector2d* position){
  printf("(%d,%d)\n", position->x, position->y);
}

Vector2d* Vector2d__add(Vector2d* position1, Vector2d* position2){
  Vector2d* v=Vector2d__create(position1->x+position2->x, position1->y+position2->y);
}

Vector2d* Vector2d__subtract(Vector2d* position1, Vector2d* position2){
  Vector2d* v=Vector2d__create(position1->x-position2->x, position1->y-position2->y);
}

Animal* Animal__create(int x, int y, MapDirection orientation){
  Animal* animal=malloc(sizeof(Animal));
  animal->position = Vector2d__create(x,y);
  animal->orientation=orientation;
}
char* Kierunki(MapDirection m){
  if(m==0)
    return "Północ";
  if(m==1)
    return "Południe";
  if(m==2)
    return "Zachód";
  if(m==3)
    return "Wschód";
}

char* Animal__toString(Animal* animal){
  char* str=malloc(30*sizeof(char));
  snprintf(str, sizeof(str)*5, "(%d, %d, %s)", animal->position->x, animal->position->y, Kierunki(animal->orientation));
  return str;
}

void Animal__move(Animal* animal, MoveDirection dir[]){
  MapDirection directions;
  for(int i=0; i<dl; i++){
    directions=dir[i];
  if(directions==0){
    animal->position->y++;
    animal->orientation=NORTH;
  }
  if(directions==1){
    animal->position->y--;
    animal->orientation=SOUTH;
  }
  if(directions==2){
    animal->position->x++;
    animal->orientation=EAST;
  }
  if(directions==3){
    animal->position->x--;
    animal->orientation=WEST;
  }
  }
}

/*int main(void){
  MoveDirection d[]={RIGHT, RIGHT};
  Vector2d* v=Vector2d__create(2,3);
  Vector2d* v1=Vector2d__add(v,v);
  Vector2d* v2=Vector2d__subtract(v1,v);
  Vector2d__toString(v2);
  Animal* cat=Animal__create(2, 2, NORTH);
  Animal__toString(cat);
  dl=2;
  Animal__move(cat, d);
  Animal__toString(cat);
  printf("hi");
  }*/

void test_toString(){
  Animal* cat=Animal__create(1, 2, NORTH);
  CU_ASSERT_STRING_EQUAL(Animal__toString(cat), "(1, 2, Północ)");
}

void test_AnimalMove(){
  MapDirection d[]={RIGHT, RIGHT};
  Animal* cat=Animal__create(2, 2, NORTH);
  dl=2;
  Animal__move(cat, d);
  CU_ASSERT_STRING_EQUAL(Animal__toString(cat), "(4, 2, Wschód)");
}

int main(){
  CU_pSuite pSuite = NULL;

  if(CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  pSuite = CU_add_suite("test4", 0,0);
  if(NULL == pSuite){
    CU_cleanup_registry();
    return CU_get_error();
  }

  //---------------------------------------------------------
  if((NULL == CU_add_test(pSuite, "Animal__toString()", test_toString))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  if((NULL == CU_add_test(pSuite, "Animal__MoveDirection()", test_AnimalMove))){
    CU_cleanup_registry();
    return CU_get_error();
  }

  //---------------------------------------------------------

  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}

