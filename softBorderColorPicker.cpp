#include "softBorderColorPicker.h"

SoftBorderColorPicker::SoftBorderColorPicker(unsigned int width, PNG& inputimage, double tol) : 
    borderwidth(width), img(inputimage), tolerance(tol) {}

HSLAPixel SoftBorderColorPicker::operator()(point p)
{
    int ex = p.x;
    int why = p.y;
    unsigned int dist = (int)tolerance;

    double avgA = img.getPixel(ex, why)->a;
    double avgS = img.getPixel(ex, why)->s;
    double avgH = img.getPixel(ex, why)->h;
    double avgL = img.getPixel(ex, why)->l;
    int counter = 0;

    if (dist < borderwidth) {
        avgA = 0, avgS = 0, avgH = 0, avgL = 0;
        int left = ex - borderwidth;
        int upper = why - borderwidth;
    
        for (unsigned int i = left; i < left + borderwidth * 2; i++) {
            for (unsigned int j = upper; j < upper + borderwidth * 2; j++) {
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
    }
    HSLAPixel pix(avgH, avgS, avgL, avgA);
    return pix;
}
