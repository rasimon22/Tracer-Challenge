//
// Created by Rick Simon on 2019-01-15.
//

#include "Matrix.h"
#include "Tuple.h"

Primitives::Matrix::Matrix(): width(4), height(4), data(std::make_unique<float[]>(16)) {
    std::memset(data.get(), 0, sizeof(float) * width * height);
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

bool Primitives::Matrix::operator==(const Primitives::Matrix& rhs) const{
    if(height == rhs.height && width == rhs.width){
        float* l_ptr = &data[0];
        float* r_ptr = &rhs.data[0];
        for(auto i = 0; i < width * height; ++i){
            if(*l_ptr != * r_ptr) return false;
            ++l_ptr;
            ++r_ptr;
        }
        return true;
    }
    return false;
}

Primitives::Matrix Primitives::Matrix::operator*(Primitives::Matrix &rhs){
    if(width != rhs.height){
        throw "Mismatched Dimensions";
    }
    Matrix m(height, rhs.width);
    for(auto row = 0; row < m.height; ++row){
        for(auto column = 0; column < m.width; ++column){
            m.at(column, row) = calculateCell(column, row, *this, rhs);
        }
    }
    return m;
}

float Primitives::Matrix::calculateCell(size_t x, size_t y, Primitives::Matrix & m1, Primitives::Matrix &m2) {
    float result = 0;
    for(auto i = 0; i < m1.width; ++i) {
        result += m1.at(i, y) * m2.at(x, i);
    }
    return result;
}

Primitives::Matrix Primitives::Matrix::operator*(Primitives::Tuple &rhs) {
    if(width != 4){
        throw "Mismatched Dimensions";
    }
    Matrix m(1,4);
    m.at(0,0) = rhs.x;
    m.at(0,1) = rhs.y;
    m.at(0,2) = rhs.z;
    m.at(0,3) = rhs.w;
    Matrix result(1,4);

    for(auto row = 0; row < m.height; ++row){
        for(auto column = 0; column < m.width; ++column){
            result.at(column, row) = calculateCell(column, row, *this, m);
        }
    }
    return result;
}

