#ifndef SOURCE_H
#define SOURCE_H

#include <stdio.h>
#include "image.h"

class Source {
    public:
        Image *image;
    public:
        virtual void Execute()=0;
        void setImage(Image *param_image){
            this->image =param_image;
        }
        Image * GetOutput(){
            return this->image;
        }
};

#endif