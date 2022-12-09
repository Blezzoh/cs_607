#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pixel
typedef struct
{
   unsigned char r, g, b;
} Pixel;

typedef struct
{
   int w, h;
   Pixel *img;
} Image;

Image *
ReadImage(char *filename)
{
   /* These lines are useful:*/

   FILE *f_in = fopen(filename, "r");

   char magicNum[128];
   int width, height, maxval;

   //  where f_in is the name of the input FILE.
   fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
   //printf(" f=%s w=%d h=%d max=%d pos =%ld", magicNum, width, height, maxval, ftell(f_in));

   // initialize the return values
   Image *value_to_return = malloc(sizeof(Image));
   Pixel *image = malloc(sizeof(Pixel) * width * height);
   
   
   for (int i=0; i<height; i++){
      for(int j=0; j<width; j++){
         fscanf(f_in,"%c%c%c",&image[i*width + j].r,&image[i*width + j].g,&image[i*width + j].b);
         // printf("%u %u %u\n", (unsigned int)image[i*width + j].r, (unsigned int)image[i*width + j].g, (unsigned int)image[i*width + j].b);
      }  
   }

   value_to_return->h = height;
   value_to_return->w = width;
   value_to_return->img = image;
   fclose(f_in);
   
   return value_to_return;
}

void WriteImage(Image *img, char *filename)
{
   FILE *f_out = fopen(filename, "w");
   Pixel *pixels = img->img;
   int height = img->h;
   int width = img->w;

   fprintf(f_out, "P6\n%d %d\n%d\n",img->w,img->h,255);

   for (int i=0; i<height; i++){
      for(int j=0; j<width; j++){
         fprintf(f_out,"%c%c%c",pixels[i*width + j].r,pixels[i*width + j].g,pixels[i*width + j].b);
         // printf("%u %u %u\n", (unsigned int)image[i*width + j].r, (unsigned int)image[i*width + j].g, (unsigned int)image[i*width + j].b);
      }  
   }
   fclose(f_out);

}

Image *
YellowDiagonal(Image *input)
{
   Pixel *image = input->img;
   int width = input->w;
   unsigned char r = (unsigned char) 255;
   unsigned char g = (unsigned char) 255;
   unsigned char b = (unsigned char) 0;
   for(int i =0; i<input->h; i++){
      image[i * width + i].r = r;
      image[i * width + i +1].g = g;
      image[i * width + i+3].b = b;
   }
   return input;
}

int main(int argc, char *argv[])
{
   /* Read an image, apply yellow diagonal to it, then write */
   if (argc == 3)
   {
      // input, output file
      
      FILE *file_out;

      // string
      char *input = argv[1];
      char *output = argv[2];


      Image *myImage = ReadImage(input);
      myImage =  YellowDiagonal(myImage);
      WriteImage(myImage, output);

      free(myImage->img);
      free(myImage);
      exit(0);
   }
   else
   {
      printf("problem, you have %d args, you need only 3 arguments\n", argc);
   }
}
