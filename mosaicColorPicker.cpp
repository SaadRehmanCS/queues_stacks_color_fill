#include "mosaicColorPicker.h"

MosaicColorPicker::MosaicColorPicker(int mosaicwidth, PNG& inputimage) : width(mosaicwidth), img(inputimage) {
  //PNG mosaic = new PNG(inputimage);

  for (unsigned int i = 0; i < inputimage.width(); i += width) {
    for (unsigned int j = 0; j < inputimage.height(); j += width) {
      mosaicifyBlock(i, j);
    }
  }
  }

void MosaicColorPicker::mosaicifyBlock(int left, int upper) {
  double avgA = 0, avgS = 0, avgH = 0, avgL = 0;
  int counter = 0;
  
  for (int i = left; i < left + width; i++) {
    for (int j = upper; j < upper + width; j++) {
      avgA += img.getPixel(i, j)->a;
      avgH += img.getPixel(i, j)->h;
      avgS += img.getPixel(i, j)->s;
      avgL += img.getPixel(i, j)->l;
      counter++;
    }
  }

  avgL /= counter;
  avgH /= counter;
  avgA /= counter;
  avgS /= counter;

  for (int i = left; i < left + width; i++) {
    for (int j = upper; j < upper + width; j++) {
      mosaicimg.getPixel(i, j)->a = avgA;
      mosaicimg.getPixel(i, j)->h = avgH;
      mosaicimg.getPixel(i, j)->l = avgL;
      mosaicimg.getPixel(i, j)->s = avgS;
    }
  }
}

HSLAPixel MosaicColorPicker::operator()(point p)
{
  double avgH = mosaicimg.getPixel(p.x, p.y)->h;
  double avgS = mosaicimg.getPixel(p.x, p.y)->s;
  double avgL = mosaicimg.getPixel(p.x, p.y)->l;
  double avgA = mosaicimg.getPixel(p.x, p.y)->a;

HSLAPixel pix(avgH, avgS, avgL, avgA);
return pix;
}
