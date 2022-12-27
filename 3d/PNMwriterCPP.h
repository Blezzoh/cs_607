#ifndef PNMWRITERCPP_H
#define PNMWRITERCPP_H

#include "sink.h"
#include <fstream>
#include <ostream>

class PNMwriterCPP: public Sink{
    private:
        char * filename;
    public:
        void Write(char *);

};

#endif