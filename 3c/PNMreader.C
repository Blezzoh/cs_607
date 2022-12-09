#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include "PNMreader.h"
#include "image.h"


PNMreader::PNMreader(char * filename_in)
{
    this->filename = (char *) malloc(sizeof(filename_in));
    this->filename = strcpy(filename_in, this->filename);
    
    // creating an image
}

void PNMreader::Execute(){

    FILE * f_in = fopen(this->filename, "r");
    char magicNum[128];
    int width, height, maxval;

    //  where f_in is the name of the input FILE.
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

    this->image->ResetSize(width,height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            unsigned char r,g,b;
            fscanf(f_in, "%c%c%c",&r, &g, &b);
            this->image->GetImage()[i * width + j].setRgb(r,g,b);
        }
    };

    fclose(f_in);
}
PNMreader::~PNMreader(){
    free(this->filename);
    // free(this->image); // think about freeing the image space
    printf("filename space freed");
}

