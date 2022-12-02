#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){
    if(argc == 3){
        // input, output file
        FILE *file_in;
        FILE *file_out;

        // string 
        char *input = argv[1];
        char *output = argv[2];

        // input file, output file
        file_in= fopen(input, "r");
        file_out = fopen(output, "w");
        if( file_in == NULL || file_out == NULL){
            printf("Error cannot open one of the files");
            exit(1);
        }

        int **content = malloc(5*5 * sizeof(int));
        int CONTENT_SIZE = 5;
       
        
        for(int i =0; i<5; i++){
            fread(content[i], sizeof(int), CONTENT_SIZE, file_in);
            fseek(file_in, 40, SEEK_CUR);
            printf("%d\n", i);
        }

        printf("\n n %d ", content[0][2]);
        fclose(file_in);
        fclose(file_out);
        free(content);
        exit(0);

    }
    else{
        printf("problem, you have %d args, you need only 3 arguments\n", argc);
    }
}