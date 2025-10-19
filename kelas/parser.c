// production rules:
// S -> Ab
// A -> aAb
// A -> e


#include <stdio.h>
int parserA2(char A2);
int parserA1(char A1);
int parserS( char S);
int bCheckValuePresent(char arr[], char value1, char value2);
int main(void){

    char alphabet[2] = {'S', 'A'};

   vGrammarRule(alphabet, alphabet, NULL);


    return 0;
}


int parserS (char S){
    if (S != 'S'){
        return -1;
    }
    printf("Ab");
    return 1;
}

int parserA1(char A1){
    if (A1 != 'A'){
        return -1;
    }
    printf("aAb");
    return 1;
}

int parserA2(char A2){
    if (A2 != 'A'){
        return -1;
    }
    printf("e");
    return 1;
}

void vGrammarRule(char* alphabet, char* variable, char start){
    while (bCheckValuePresent(variable, variable[0], variable[1]) == 1){
        parserS(alphabet[0]);
        parserA2(alphabet[1]);
        parserA1(alphabet[2]);
    }
}


int bCheckValuePresent(char arr[], char value1, char value2){
    int arraysize =  sizeof(arr[])/sizeof(arr[0]);
    for (int i = 0; i < arraysize; i++){
        if (arr[i] == value1 || arr[i] == value2){
            return 1;
        }
        else{
            return -1;
        }
    }
}