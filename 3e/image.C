#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"


void Pixel::setRgb(unsigned char p_r, unsigned char p_g, unsigned char p_b)
{
    this->r = p_r;
    this->g = p_g;
    this->b = p_b;
}

Image::Image()
{
    this->h = 0;
    this->w = 0;
}
Image::Image(int width, int height)
{
    this->w = width;
    this->h = height;
    this->img = (Pixel *) malloc(h * w * sizeof(Pixel));
}

Image::Image(Image &originalImage)
{

    int size_img = originalImage.h * originalImage.w * sizeof(Pixel);
    Pixel *pixels = (Pixel *)malloc(size_img);
    memcpy(pixels, originalImage.img, size_img);

    this->img = pixels;
    this->w = originalImage.w;
    this->h = originalImage.h;
}
Image::Image(int width, int height, Pixel * pixels){
    this->h = height;
    this->w = width;
    this->img = pixels;
}

void Image::ResetSize(int width, int height)
{
    this->w = width;
    this->h = height;
    this->img = (Pixel *)malloc(h * w * sizeof(Pixel));
}

void Image::ResetSize(int width, int height, Pixel * image_space){
    this->w = width;
    this->h = height;
    this->img = image_space;
}

void Image::Update(){
    printf("image.c update\n");
}


