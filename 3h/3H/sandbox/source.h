#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include "image.h"

class Source {
    protected:
        Image * image1 = new Image();
        Image * image2 = new Image();
        Image * imageOut = new Image();
    public:
        virtual void Update()=0;
        virtual void Execute()=0;
        virtual const char *SourceName() =0;
        Image * GetOutput();
};

#endif