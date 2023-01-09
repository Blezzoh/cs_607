#include "image.h"
#include "logging.h"
#include "sink.h"
#include <cstdio>

void Sink::SetInput(Image *img) { this->inputImage = img; }
void Sink::SetInput2(Image *img) { this->outputImage = img; }

Image *Sink::getImage() { return this->inputImage; }

const char *CheckSum::Name() { return "CheckSum"; }

void CheckSum::OutputCheckSum(const char * filename) {
  if (!this->getImage()) {
    char msg[128] = "Missing input1";
    DataFlowException err(Name(), msg);
    throw err;
  }
  else{
    printf("start checksum ...");

    int r=0, g=0, b=0;
    int h = this->getImage()->getHeight();
    int w = this->getImage()->getWidth();
    Pixel * original = this->getImage()->GetImage();
    FILE * f_out = fopen(filename, "w");
    printf("calculating checksum ..., %d, %d", h,w);
    for (int i = 0; i < h; i++) {
      for (int j =0; j < w; j++) {
        r +=(int) original[i * w + j].GetR();
        g +=(int) original[i * w + j].GetG();
        b +=(int)original[i * w + j].GetB();
      }
    }
    r = r %256;
    b = b %256;
    g = g %256;
    fprintf(f_out, "CHECKSUM: %d, %d, %d\n", r, g, b);
    fclose(f_out);
  }
}