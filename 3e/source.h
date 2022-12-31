#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include "image.h"

class Source: protected Image {
    protected:
        Image * image1 = new Image();
        Image * image2 = new Image();
        Image * imageOut = new Image();
    public:
        virtual void Execute()=0;
        Image * GetOutput();
        virtual void Update();
};

#endif