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
const char *Mirror::Name() { return "Mirror"; }
const char *Rotate::Name() { return "Rotate"; }
const char *Subtract::Name() { return "Subtract"; }
const char *Grayscale::Name() { return "Grayscale"; }
const char *Blur::Name() { return "Blur"; }
const char *Color::Name() { return "Color"; }

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

Color::Color(int _w, int _h, int _r, int _g, int _b) {
  r = _r;
  g = _g;
  b = _b;
  w = _w;
  h = _h;
}

void Color::Execute() {
  Pixel *img_space = (Pixel *)malloc(sizeof(Pixel) * this->w * this->h);
  for (int i = 0; i < h * w; i++) {
    img_space[i].setRgb(r, g, b);
  }
  this->GetOutput()->ResetSize(w, h, img_space);
}

void Blur::Execute() {
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

    Pixel *img_space = (Pixel *)malloc(h * w * sizeof(Pixel));
    Pixel *original = this->GetInput1()->GetImage();

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (i > 0 && j > 0 && j < w - 1 && i < h - 1) {

          unsigned char r = (original[i * w + j - 1].r) / 8 +
                            (original[i * w + j + 1].r) / 8 +
                            (original[(i + 1) * w + j - 1].r) / 8 +
                            (original[(i + 1) * w + j + 1].r) / 8 +
                            (original[(i + 1) * w + j].r) / 8 +
                            (original[(i - 1) * w + j - 1].r) / 8 +
                            (original[(i - 1) * w + j + 1].r) / 8 +
                            (original[(i - 1) * w + j].r) / 8;
          unsigned char g = (original[i * w + j - 1].g) / 8 +
                            (original[i * w + j + 1].g) / 8 +
                            (original[(i + 1) * w + j - 1].g) / 8 +
                            (original[(i + 1) * w + j + 1].g) / 8 +
                            (original[(i + 1) * w + j].g) / 8 +
                            (original[(i - 1) * w + j - 1].g) / 8 +
                            (original[(i - 1) * w + j + 1].g) / 8 +
                            (original[(i - 1) * w + j].g) / 8;
          unsigned char b = (original[i * w + j - 1].b) / 8 +
                            (original[i * w + j + 1].b) / 8 +
                            (original[(i + 1) * w + j - 1].b) / 8 +
                            (original[(i + 1) * w + j + 1].b) / 8 +
                            (original[(i + 1) * w + j].b) / 8 +
                            (original[(i - 1) * w + j - 1].b) / 8 +
                            (original[(i - 1) * w + j + 1].b) / 8 +
                            (original[(i - 1) * w + j].b) / 8;
          img_space[i * w + j].setRgb(r, g, b);
        } else {
          // edges
          unsigned char r = original[i * w + j].r;
          unsigned char g = original[i * w + j].g;
          unsigned char b = original[i * w + j].b;

          img_space[i * w + j].setRgb(r, g, b);
        }
      }
    }
    this->GetOutput()->ResetSize(w, h, img_space);
  }
}

void Grayscale::Execute() {
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

    Pixel *img_space = (Pixel *)malloc(h * w * sizeof(Pixel));
    Pixel *original = this->GetInput1()->GetImage();

    for (int i = 0; i < h * w; i++) {
      int val = original[i].r / 5 + original[i].g / 2 + original[i].b / 4;
      img_space[i].setRgb(val, val, val);
    }
    this->GetOutput()->ResetSize(w, h, img_space);
  }
}
void Rotate::Execute() {
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

    Pixel *img_space = (Pixel *)malloc(h * w * sizeof(Pixel));
    Pixel *original = this->GetInput1()->GetImage();

    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {

        unsigned char r = original[i * w + j].GetR();
        unsigned char g = original[i * w + j].GetG();
        unsigned char b = original[i * w + j].GetB();
        img_space[j * h + h - i - 1].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(h, w, img_space);
  }
}

void Mirror::Execute() {
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

    Pixel *img_space = (Pixel *)malloc(h * w * sizeof(Pixel));
    Pixel *original = this->GetInput1()->GetImage();

    for (int i = 0; i < h; i++) {
      for (int j = w - 1, k = 0; j >= 0 && k < w; j--, k++) {

        unsigned char r = original[i * w + k].GetR();
        unsigned char g = original[i * w + k].GetG();
        unsigned char b = original[i * w + k].GetB();
        img_space[i * w + j].setRgb(r, g, b);
      }
    }
    this->GetOutput()->ResetSize(w, h, img_space);
  }
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

    // printf("w%d h%d w.%d h.%d\n", w, h, o_w, o_h);

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

void Subtract::Execute() {
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

    Pixel *left = leftInput->GetImage();
    Pixel *right = rightInput->GetImage();

    Pixel *pixels = (Pixel *)malloc(sizeof(Pixel) * h * w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        unsigned char r_l = (left[i * w + j].GetR());
        unsigned char r_r = ((right[i * w + j].GetR()));
        unsigned char g_l = ((left[i * w + j].GetG()));
        unsigned char g_r = ((right[i * w + j].GetG()));
        unsigned char b_l = ((left[i * w + j].GetB()));
        unsigned char b_r = ((right[i * w + j].GetB()));
        // substrack left from right
        int r = (r_l - r_r);
        int g = (g_l - g_r);
        int b = (b_l - b_r);
        // max of 0 and color
        r = r < 0 ? 0 : r;
        g = g < 0 ? 0 : g;
        b = b < 0 ? 0 : b;
        pixels[i * w + j].setRgb((unsigned char)r, (unsigned char)g,
                                 (unsigned char)b);
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
