#define FOR(i,n) for(int i=0; i<n; i++)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 100

char * getASCIIHex(char znak){
    char temp[2];
    sprintf(temp, "%x", znak);
    return temp;
}

char ** getData(int *count){
    int lineCount = 2;
    *count = 0;
    char ** text = (char **) malloc(3 * sizeof(*text));
    for (int i=0; i<3; i++){
        text[i] = (char *) malloc(LEN * sizeof(char));
    }
    for(int i=0; i<3; i++){
        (*count)++;
        if (fgets(text[i], LEN, stdin) == 0){
            lineCount = 0;
            for(int j=i; i<3; j++){
                free(text[i]);
                text[i]=0;
            }
            break;
        }
        else{
            printf("%s\n", text[i]);
        }
    }
    while(lineCount){
        //(*count)++;
        text = (char **) realloc(text, (++lineCount)*sizeof(*text));
        text[lineCount] = (char *) malloc(LEN * sizeof(char));
        if (fgets(text[i], LEN, stdin) == 0){
            lineCount = 0;
        }
        else{
            (*count)++;
            printf("%s\n", text[lineCount]);
        }
    }
    return text;
}
int main(void)
{
 //char a='(';
 //char *aa=getHexAscii(a);
 //printf("%s\n", aa);
 int *wiersze =(int *) malloc(sizeof(int));
 (*wiersze)=0;
 char **aaa=getData(wiersze);
 FOR(i,*wiersze)
 free(aaa[i]);
 free(aaa);
}
