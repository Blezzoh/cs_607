#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    if(argc>= 3){
        printf("number of arguments %d\n", argc);
    }
    else{
        printf("problem, you have %d args, you need 3 arguments\n", argc);
    }
}