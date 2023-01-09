#ifndef FILTER_H
#define FILTER_H

#include "source.h"

class Filter : public Source {
public:
  Filter();
  Image *GetInput1() { return image1; }
  Image *GetInput2() { return image2; }
  void SetInput2(Image *img) { this->image2 = img; }
  void SetInput(Image *img) { this->image1 = img; }
  void Update();
  virtual const char *Name()=0;
  const char *SourceName();
};

class Shrinker : public Filter {

public:
  virtual void Execute();
  virtual const char *Name();

};

class LRCombine : public Filter {
public:
  virtual void Execute();
  virtual const char *Name();
};

class TBCombine : public Filter {
public:
  virtual void Execute();
  virtual const char *Name();
};

class Blender : public Filter {
private:
  double factor;

public:
  virtual void Execute();
  void SetFactor(double db) { this->factor = db; }
  double GetFactor() { return this->factor; }
  virtual const char *Name();
};

#endif