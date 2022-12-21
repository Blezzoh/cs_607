#ifndef  PNMREADER_H
#define PNMREADER_H


#include <stdio.h>
#include "image.h"
#include "source.h"
#include <string>

class PNMreader: public Source
{
    private:
        char *  filename;
    public:
        virtual void Execute();
        PNMreader(char * filename);
        ~PNMreader();
    
};

#endif
