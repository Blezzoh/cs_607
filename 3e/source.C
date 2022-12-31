#include "source.h"
#include <cstdio>

Image * Source::GetOutput() { return this->imageOut; }

void Source::Update(){
    this->imageOut->Update();
    printf("source.c update");
}