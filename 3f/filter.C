#include "filter.h"
#include "image.h"
#include "logging.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>

const char *TBCombine::Name() { return "TBCombine"; }
const char *LRCombine::Name() { return "LRCombine"; }
const char *Blender::Name() { return "Blender"; }
const char *Shrinker::Name() { return "Shrinker"; }

Filter::Filter() {
  Source::image1 = NULL;
  Source::image2 = NULL;
  Source::imageOut->setSource(this);
}
const char *Filter::SourceName() { return Name(); }

void Filter::Update() {
  char msg[128];
  if (Source::image1) {
    sprintf(msg, "%s is about to update image 1.", SourceName());
    Logger::LogEvent(msg);
    Source::image1->Update();
    sprintf(msg, "%s is done  updating image 1.", SourceName());
    Logger::LogEvent(msg);
  }
  if (Source::image2) {
    sprintf(msg, "%s is about to update image 2.", SourceName());
    Logger::LogEvent(msg);
    Source::image2->Update();
    sprintf(msg, "%s is done  updating image 2.", SourceName());
    Logger::LogEvent(msg);
  }
  sprintf(msg, "%s: about to execute", SourceName());
  Logger::LogEvent(msg);
  Execute();
  sprintf(msg, "%s: done executing", SourceName());
  Logger::LogEvent(msg);
}

void Shrinker::Execute() {
  if (!this->GetInput1()) {
    char msg[128] = "Missing input1";
    DataFlowException err(Name(), msg);
    throw err;
  } else {

    char msg[128];
    sprintf(msg, "Executing ... %s", Name());
    Logger::LogEvent(msg);

    int h = this->GetInput1()->getHeight();
    int w = this->GetInput1()->getWidth();
    int o_h = (int)((double)h / 2.0);
    int o_w = (int)((double)w / 2.0);
    Pixel *img_space = (Pixel *)malloc(o_h * o_w * sizeof(Pixel));
    Pixel *original = this->GetInput1()->GetImage();

    printf("w%d h%d w.%d h.%d\n", w, h, o_w, o_h);

    for (int i = 0; i < o_h; i++) {
      for (int j = 0; j < o_w; j++) {

        unsigned char r = original[(i * 2) * w + (j * 2)].GetR();
        unsigned char g = original[(i * 2) * w + (j * 2)].GetG();
        unsigned char b = original[(i * 2) * w + (j * 2)].GetB();
        img_space[i * o_w + j].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(o_w, o_h, img_space);
  }
}
void LRCombine::Execute() {
  bool hasError = false;
  if (!this->GetInput1()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input1");
    throw err;
  }
  if (!this->GetInput2()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input2");
    throw err;
  }

  Image *leftInput = this->GetInput1();
  Image *rightInput = this->GetInput2();

  int h = leftInput->getHeight();

  if (this->GetInput1()->getHeight() != this->GetInput2()->getHeight()) {
    hasError = true;
    char msg[256];
    sprintf(msg, "||%s: height of input 1(%d) is different from input2 (%d)",
            Name(), h, this->GetInput2()->getHeight());
    DataFlowException err(Name(), msg);
    throw err;
  }
  if (!hasError) {
    char msg[128];
    sprintf(msg, "Executing ... %s", Name());
    Logger::LogEvent(msg);

    int w = leftInput->getWidth() + rightInput->getWidth();
    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * h * w);
    printf("LRcombine = w%d h%d \n", h, w);

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < leftInput->getWidth(); j++) {
        // use left image
        unsigned char r =
            leftInput->GetImage()[i * leftInput->getWidth() + j].GetR();
        unsigned char g =
            leftInput->GetImage()[i * leftInput->getWidth() + j].GetG();
        unsigned char b =
            leftInput->GetImage()[i * leftInput->getWidth() + j].GetB();
        pixels[i * w + j].setRgb(r, g, b);
      }
    }
    for (int i = 0; i < h; i++) {
      for (int j = leftInput->getWidth(); j < w; j++) {
        // use right image
        int k = j - leftInput->getWidth();
        unsigned char r =
            rightInput->GetImage()[i * rightInput->getWidth() + k].GetR();
        unsigned char g =
            rightInput->GetImage()[i * rightInput->getWidth() + k].GetG();
        unsigned char b =
            rightInput->GetImage()[i * rightInput->getWidth() + k].GetB();
        pixels[i * w + j].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(w, h, pixels);
  }
}

void TBCombine::Execute() {
  bool hasError = false;
  if (!this->GetInput1()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input1");
    throw err;
  }
  if (!this->GetInput2()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input2");
    throw err;
  }
  Image *topInput = this->GetInput1();
  Image *bottomInput = this->GetInput2();

  int w = topInput->getWidth();
  if (this->GetInput1()->getHeight() != this->GetInput2()->getHeight()) {
    hasError = true;
    char msg[256];
    sprintf(msg, "||%s: width of input 1(%d) is different from input2 (%d)",
            Name(), w, this->GetInput2()->getWidth());
    DataFlowException err(Name(), msg);
    throw err;
  }
  if (!hasError) {
    char msg[128];
    sprintf(msg, "Executing ... %s", Name());
    Logger::LogEvent(msg);

    int h = topInput->getHeight() + bottomInput->getHeight();
    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * h * w);
    for (int i = 0; i < topInput->getHeight(); i++) {
      for (int j = 0; j < w; j++) {
        Pixel p = topInput->GetImage()[i * w + j];
        unsigned char r = p.GetR();
        unsigned char g = p.GetG();
        unsigned char b = p.GetB();

        pixels[i * w + j].setRgb(r, g, b);
      }
    }
    for (int i = topInput->getHeight(); i < h; i++) {
      for (int j = 0; j < w; j++) {
        int k = (i - topInput->getHeight());
        Pixel p = bottomInput->GetImage()[k * w + j];

        unsigned char r = p.GetR();
        unsigned char g = p.GetG();
        unsigned char b = p.GetB();

        pixels[i * w + j].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(w, h, pixels);
  }
}

void Blender::Execute() {
  bool hasError = false;
  if (!this->GetInput1()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input1");
    throw err;
  }
  if (!this->GetInput2()) {
    hasError = true;
    DataFlowException err(Name(), "Missing input2");
    throw err;
  }
  if (this->GetFactor() > 1.0) {
    hasError = true;
    DataFlowException err(Name(), "Blender factor exceeds 1.0");
    throw err;
  }
  if (this->GetFactor() < 0.0) {
    hasError = true;
    DataFlowException err(Name(), "Blender factor is less than 0.0");
    throw err;
  }
  if (this->GetFactor() > 1.0) {
    hasError = true;
    DataFlowException err(Name(), "Blender factor exceeds 1.0");
    throw err;
  }

  Image *leftInput = this->GetInput1();
  Image *rightInput = this->GetInput2();
  double factor = this->GetFactor();
  int h = leftInput->getHeight();
  int w = leftInput->getWidth();

  if (this->GetInput1()->getHeight() != this->GetInput2()->getHeight()) {
    hasError = true;
    char msg[256];
    sprintf(msg, "||%s: width of input 1(%d) is different from input2 (%d)",
            Name(), w, this->GetInput2()->getWidth());
    DataFlowException err(Name(), msg);
    throw err;
  }
  if (this->GetInput1()->getHeight() != this->GetInput2()->getHeight()) {
    hasError = true;
    char msg[256];
    sprintf(msg, "||%s: height of input 1(%d) is different from input2 (%d)",
            Name(), h, this->GetInput2()->getHeight());
    DataFlowException err(Name(), msg);
    throw err;
  }
  if (!hasError) {
    char msg[128];
    sprintf(msg, "Executing ... %s", Name());
    Logger::LogEvent(msg);

    double factor_left = 1.0 - factor;
    Pixel *left = leftInput->GetImage();
    Pixel *right = rightInput->GetImage();

    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * h * w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        double r_l = ((double)(left[i * w + j].GetR())) * factor;
        double r_r = ((double)(right[i * w + j].GetR())) * factor_left;
        double g_l = ((double)(left[i * w + j].GetG())) * factor;
        double g_r = ((double)(right[i * w + j].GetG())) * factor_left;
        double b_l = ((double)(left[i * w + j].GetB())) * factor;
        double b_r = ((double)(right[i * w + j].GetB())) * factor_left;
        unsigned char r = (unsigned char)(r_l + r_r);
        unsigned char g = (unsigned char)(g_r + g_l);
        unsigned char b = (unsigned char)(b_r + b_l);
        pixels[i * w + j].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(w, h, pixels);
  }
}
