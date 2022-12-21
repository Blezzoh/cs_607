#include "image.h"
#include "sink.h"
#include "PNMwriter.h"


void PNMwriter::Write(char * filename_out){
    FILE *f_out = fopen(filename_out, "w");
    Image * img = this->getImage();
    Pixel *pixels = img->GetImage();
    int height = img->getHeight();
    int width = img->getWidth();

    fprintf(f_out, "P6\n%d %d\n%d\n", width, height, 255);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fprintf(f_out, "%c%c%c", pixels[i * width + j].r, pixels[i * width + j].g, pixels[i * width + j].b);
            // printf("%u %u %u\n", (unsigned int)image[i*width + j].r, (unsigned int)image[i*width + j].g, (unsigned int)image[i*width + j].b);
        }
    }
    fclose(f_out);
}