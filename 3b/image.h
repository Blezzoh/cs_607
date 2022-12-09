#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

struct Pixel{
    unsigned char r, g, b;
    void setRgb(unsigned char p_r, unsigned char p_g, unsigned char p_b);
};

struct Image
{
    int w, h;
    Pixel *img;
    Image(void);
    Image(int width, int height);
    Image(Image &);
    void ResetSize(int width, int height);
    void ResetSize(int width, int height, Pixel *img_space);
};

#endif