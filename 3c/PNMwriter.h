#ifndef PNMWRITER_H
#define PNMWRITER_H

#include "sink.h"

class PNMwriter: public Sink{
    private:
        char * filename;
    public:
        void Write(char *);

};

#endif