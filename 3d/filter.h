#ifndef FILTER_H
#define FILTER_H

#include "image.h"
#include "source.h"

class Filter : public Source {
public:
  Image *imageOut = new Image();
  Image *image1 = new Image();
  Image *image2 = new Image();
public:
  Image *GetInput1(){return image1;}
  Image *GetInput2(){return image2;}
  Image *GetOutput(){return imageOut;}
  void SetInput2(Image *img) { this->image2 = img; }
  void SetInput(Image *img) { this->image1 = img; }
};

class Shrinker : public Filter {

public:
  virtual void Execute();
};

class LRCombine : public Filter {
public:
  virtual void Execute();
};

class TBCombine : public Filter {
public:
  virtual void Execute();
};

class Blender : public Filter {
private:
  double factor;

public:
  virtual void Execute();
  void SetFactor(double db) { this->factor = db; }
  double GetFactor() { return this->factor; }
};

#endif