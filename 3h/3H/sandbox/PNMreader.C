#include "source.h"
#include "PNMreader.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdio.h>
using namespace std;

PNMreader::PNMreader(char *filename_in) {
  // printf("\npnm filename= %s\n", filename_in);

  this->filename = filename_in;
  this->imageOut->setSource(this);

}

void PNMreader::Execute() {
  ifstream f_in(this->filename);
  char magicNum[2];
  // char c;
  int width, height, maxval;

  f_in >> magicNum>>width>>height>>maxval;
  // printf("something1 %s\n%d %d\n%d\n", magicNum, width, height, maxval);
  // off again
  f_in.get();
  Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * width * height);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      unsigned char r = f_in.get(), g=f_in.get(), b=f_in.get();

      pixels[i * width + j].setRgb(r, g, b);
    }
  };

  this->GetOutput()->ResetSize(width,height, pixels);
  
  f_in.close();

}

void PNMreader::Update()
{
	Execute();
}
const char * PNMreader::SourceName(){
  return "PNMreader";
}

PNMreader::~PNMreader() {
  //   free(this->filename);
  // free(this->image); // think about freeing the image space
}
