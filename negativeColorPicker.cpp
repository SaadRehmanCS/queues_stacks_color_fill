#include "negativeColorPicker.h"

NegativeColorPicker::NegativeColorPicker(PNG& inputimg) : img(inputimg) {}

HSLAPixel NegativeColorPicker::operator()(point p)
{
  double a = img.getPixel(p.x, p.y)->a;
  double h = (int)(img.getPixel(p.x, p.y)->h + 180) % 360;
  double l = 1 - img.getPixel(p.x, p.y)->l;
  double s = img.getPixel(p.x, p.y)->s;
  
  HSLAPixel pix(h, s, l, a);
  return pix;
}
