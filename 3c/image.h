#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>


class Pixel{
    private:
        unsigned char r, g, b;
    public:
        void setRgb(unsigned char p_r, unsigned char p_g, unsigned char p_b);
        unsigned char GetR(){
            return this->r;
        };
        unsigned char GetG(){
            return this->g;
        };
        unsigned char GetB(){
            return this->b;
        }

};


class Image
{
    private:
        int w, h;
        Pixel *img;
    public:
        Image(void);
        Image(int width, int height);
        Image(int width, int height, Pixel *);
        Image(Image &);
        void ResetSize(int width, int height);
        void ResetSize(int width, int height, Pixel *img_space);
        int getWidth(){return this->w;}
        int getHeight(){return this->h;}
        Pixel * GetImage(){
            return this->img;
        }
};

#endif