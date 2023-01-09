#include "image.h"
#include "sink.h"
#include "image.h"


void Sink::SetInput(Image * img){
    this->inputImage = img;
}
void Sink::SetInput2(Image * img){
    this->outputImage = img;
}

Image *Sink::getImage(){
    return this->inputImage;
}