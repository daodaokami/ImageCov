//
// Created by lut on 18-10-16.
//

#ifndef IMAGECOV_TOOLS_H
#define IMAGECOV_TOOLS_H

#include "image.h"
using namespace std;
namespace lutTools{
    class Tools {
    public:
        void Cov(const Image *image, const double *patch, const int W, const int H, const int border_type, Image *target);

    };
}

#endif //IMAGECOV_TOOLS_H
