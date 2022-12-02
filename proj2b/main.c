#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        // input, output file
        FILE *file_in;
        FILE *file_out;

        // string
        char *input = argv[1];
        char *output = argv[2];

        // input file, output file
        file_in = fopen(input, "r");
        file_out = fopen(output, "w");
        if (file_in == NULL || file_out == NULL)
        {
            printf("Error cannot open one of the files");
            exit(1);
        }

        int content[5][5];
        int CONTENT_SIZE = 5;

        for (int i = 0; i < 5; i++)
        {
            // read 5 int
            fread(content[i], sizeof(int), CONTENT_SIZE, file_in);
            // skip 5 int
            fseek(file_in, 5 * sizeof(int), SEEK_CUR);
            
            // write 5 int on 5 lines
            for(int j = 0; j<5; j++){
                fprintf(file_out, "%d\n",content[i][j]);
            }
        }

        fclose(file_in);
        fclose(file_out);
        exit(0);
    }
    else
    {
        printf("problem, you have %d args, you need only 3 arguments\n", argc);
    }
}