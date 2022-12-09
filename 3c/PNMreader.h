#include <stdio.h>
#include "image.h"
#include "source.h"

class PNMreader: public Source
{
    private:
        char * filename;
    public:
        virtual void Execute();
        PNMreader(char * filename);
        ~PNMreader();
        Image * GetOutput();
    
};
