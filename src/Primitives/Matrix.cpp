//
// Created by Rick Simon on 2019-01-15.
//

#include "Matrix.h"

Primitives::Matrix::Matrix(): width(4), height(4), data(std::make_unique<float[]>(16)) {


}

float& Primitives::Matrix::at(size_t x, size_t y) {
   return data[y*width + x];
}

Primitives::Matrix::Matrix(size_t height, size_t width): width(width), height(height),
data(std::make_unique<float[]>(width*height)){
}

//TODO:Refactor initialization out of I-list into self assignment check
Primitives::Matrix::Matrix(const Primitives::Matrix& rhs):width(rhs.width), height(rhs.height),
data(std::make_unique<float[]>(rhs.width*rhs.height)){
    for(auto i = 0; i < width*height; ++i){
        data[i] = rhs.data[i];
    }
}

Primitives::Matrix::Matrix(std::vector<float> vec, size_t width, size_t height):width(width), height(height),
data(std::make_unique<float[]>(width*height)){
   float *ptr = &data[0];
   for(auto f : vec){
     *ptr = f;
     ++ptr;
   }
}



