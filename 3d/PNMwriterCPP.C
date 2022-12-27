#include "image.h"
#include "sink.h"
#include "PNMwriterCPP.h"
#include <fstream>


void PNMwriterCPP::Write(char * filename_out){
    std::ofstream f_out(filename_out);
    Image * img = this->getImage();
    Pixel *pixels = img->GetImage();
    int height = img->getHeight();
    int width = img->getWidth();

    f_out<<"P6\n";
    f_out<< width<< "\n"<< height <<"\n"<<255<<"\n";
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            f_out << pixels[i * width + j].r << pixels[i * width + j].g <<pixels[i * width + j].b;
            // printf("%u %u %u\n", (unsigned int)image[i*width + j].r, (unsigned int)image[i*width + j].g, (unsigned int)image[i*width + j].b);
        }
    }
    f_out.close();
}