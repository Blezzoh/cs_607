#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include "image.h"

class Source {
    public:
        Image * image = new Image();
    public:
        virtual void Execute()=0;
        Image * GetOutput();
};

#endif