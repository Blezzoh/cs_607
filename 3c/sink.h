#ifndef SINK_H
#define SINK_H

#include "image.h"
#include <stdio.h>
#include "image.h"
#include "filter.h"

class Sink{
    public:
        Image *inputImage;
        Image *outputImage;
    public:
        void SetInput(Image *);
        void SetInput2(Image *);
        Image * getImage();
};

#endif