#include <stdio.h>
#include "image.h"

void ReadImage(char *filename, Image &output)
{
    /* These lines are useful:*/

    FILE *f_in = fopen(filename, "r");

    char magicNum[128];
    int width, height, maxval;

    //  where f_in is the name of the input FILE.
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);

    output.ResetSize(width, height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fscanf(f_in, "%c%c%c", &output.img[i * width + j].r, &output.img[i * width + j].g, &output.img[i * width + j].b);
        }
    };

    fclose(f_in);
}

void WriteImage(char *filename, Image &img)
{
    FILE *f_out = fopen(filename, "w");

    Pixel *pixels = img.img;
    int height = img.h;
    int width = img.w;

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

void HalfSize(Image &input, Image &output)
{
    int h = input.h;
    int w = input.w;
    int o_h = (int)((double)h / 2.0);
    int o_w = (int)((double)w / 2);
    Pixel *img_space = (Pixel *)malloc(h * w * sizeof(Pixel));
    output.ResetSize(o_w, o_h, img_space);

    for (int i = 0; i < o_h; i++)
    {
        for (int j = 0; j < o_w; j++)
        {

            unsigned char r = input.img[(i * 2) * w + (j * 2)].r;
            unsigned char g = input.img[(i * 2) * w + (j * 2)].g;
            unsigned char b = input.img[(i * 2) * w + (j * 2)].b;
            output.img[i * o_w + j].setRgb(r, g, b);
        }
    }
}

//  take two input images that have the same height, combines left image to right image to generate [left][right]
void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output)
{
    int h = leftInput.h;
    int w = leftInput.w + rightinput.w;
    output.ResetSize(w, h);
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < leftInput.w; j++)
        {
            // use left image
            unsigned char r = leftInput.img[i * leftInput.w + j].r;
            unsigned char g = leftInput.img[i * leftInput.w  + j].g;
            unsigned char b = leftInput.img[i * leftInput.w  + j].b;
            output.img[i * w + j].setRgb(r, g, b);
        }
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = leftInput.w; j < w; j++)
        {
            // use right image
            int k = j - leftInput.w;
            unsigned char r = rightinput.img[i * rightinput.w  + k].r;
            unsigned char g = rightinput.img[i * rightinput.w  + k].g;
            unsigned char b = rightinput.img[i * rightinput.w  + k].b;
            output.img[i * w + j].setRgb(r, g, b);
        }
    }
}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output)
{
    int h = topInput.h + bottomInput.h;
    int w = topInput.w;
    output.ResetSize(w, h);
    for (int i = 0; i < topInput.h; i++)
    {
        for (int j = 0; j < w; j++)
        {

            unsigned char r = topInput.img[i * w + j].r;
            unsigned char g = topInput.img[i * w + j].g;
            unsigned char b = topInput.img[i * w + j].b;
            output.img[i * w + j].setRgb(r, g, b);
        }
    }
    for (int i = topInput.h; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            int k = (i - topInput.h);
            unsigned char r = bottomInput.img[k * w + j].r;
            unsigned char g = bottomInput.img[k * w + j].g;
            unsigned char b = bottomInput.img[k * w + j].b;
            output.img[i * w + j].setRgb(r, g, b);
        }
    }
}

// takes factor of rgb leftInput and adds it to 1-factor rightInput to make output image
void Blend(Image &leftInput, Image &rightinput, double factor, Image &output)
{
    int h = leftInput.h;
    int w = leftInput.w;
    output.ResetSize(w, h);
    double factor_left = 1 - factor;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            double r_l = ((double)(leftInput.img[i * w + j].r)) * factor;
            double r_r = ((double)(rightinput.img[i * w + j].r)) * factor_left;
            double g_l = ((double)(leftInput.img[i * w + j].g)) * factor;
            double g_r = ((double)(rightinput.img[i * w + j].g)) * factor_left;
            double b_l = ((double)(leftInput.img[i * w + j].b)) * factor;
            double b_r = ((double)(rightinput.img[i * w + j].b)) * factor_left;
            unsigned char r = (unsigned char)(r_l + r_r);
            unsigned char g = (unsigned char)(g_r + g_l);
            unsigned char b = (unsigned char)(b_r + b_l);
            output.img[i * w + j].setRgb(r, g, b);
        }
    }
}