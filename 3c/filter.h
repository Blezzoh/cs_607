#ifndef FILTER_H
#define FILTER_H

#include "source.h"

class Filter: public  Source{
    public:
        Image *image2;
    public:
        Image *GetOutput2(){
            return image2;
        }
        void SetInput2(Image *img){
            this->image2 = img;
        }
        void SetInput(Image *);
};

class Shrinker:public Filter{
    
    public:
        virtual void Execute();
        
};

class LRCombine: public Filter{
    public:
        virtual void Execute();
};



class TBCombine: public  Filter{
    public:
        virtual void Execute();
};

class Blender: public  Filter{
    private:
        double factor;
    public:
        virtual void Execute();
        void SetFactor(double db){
            this->factor = db;
        }
        double GetFactor(){
            return this->factor;
        }
};

#endif