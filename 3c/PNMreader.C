#include "source.h"
#include "PNMreader.h"
#include "image.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <stdio.h>

// void write(char *filename, Image *img) {
//   FILE *f_out = fopen(filename, "w");

//   Pixel *pixels = img->GetImage();
//   int height = img->getHeight();
//   int width = img->getWidth();
//   // printf("%s\n%d %d\n%d\n", filename, width, height, 255);
//   fprintf(f_out, "P6\n%d %d\n%d\n", width, height, 255);

//   for (int i = 0; i < height; i++) {
//     for (int j = 0; j < width; j++) {
//       fprintf(f_out, "%c%c%c", pixels[i * width + j].r, pixels[i * width + j].g,
//               pixels[i * width + j].b);
//     }
//   }
//   fclose(f_out);
// }

PNMreader::PNMreader(char *filename_in) {
  printf("\npnm filename= %s\n", filename_in);

  this->filename = filename_in;
  

}

void PNMreader::Execute() {
  FILE *f_in = fopen(this->filename, "r");
  char magicNum[128];
  int width, height, maxval;

  fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
  printf("something1 %s\n%d %d\n%d\n", magicNum, width, height, maxval);

  Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * width * height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char r, g, b;
      fscanf(f_in, "%c%c%c", &r, &g, &b);
      pixels[i * width + j].setRgb(r, g, b);
    }
  };

  this->GetOutput()->ResetSize(width,height, pixels);
  
  fclose(f_in);

}
PNMreader::~PNMreader() {
  //   free(this->filename);
  // free(this->image); // think about freeing the image space
}
