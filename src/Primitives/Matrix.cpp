//
// Created by Rick Simon on 2019-01-15.
//

#include "Matrix.h"
#include "Tuple.h"
#include <cstring>

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
    for(size_t i = 0; i < width*height; ++i){
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
        for(size_t i = 0; i < width * height; ++i){
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
    for(size_t row = 0; row < m.height; ++row){
        for(size_t column = 0; column < m.width; ++column){
            m.at(column, row) = calculateCell(column, row, *this, rhs);
        }
    }
    return m;
}

float Primitives::Matrix::calculateCell(size_t x, size_t y, Primitives::Matrix & m1, Primitives::Matrix &m2) {
    float result = 0;
    for(size_t i = 0; i < m1.width; ++i) {
        result += m1.at(i, y) * m2.at(x, i);
    }
    return result;
}


void Primitives::Matrix::print(std::ostream &os) {
    for(size_t i = 0; i < height; ++i){
        for(auto j = 0; j < width; ++j){
            os << data[i * width + j] << ' ';
        }
        os << std::endl;
    }
}

Primitives::Matrix::Matrix(Primitives::Tuple &rhs): height(4), width(1){
    data = std::make_unique<float[]>(4);
    data[0] = rhs.x;
    data[1] = rhs.y;
    data[2] = rhs.z;
    data[3] = rhs.w;


}

Primitives::Matrix Primitives::Matrix::operator*(Primitives::Tuple &rhs) {
    Matrix m(rhs);
    return *this * m;
}

Primitives::Matrix Primitives::Matrix::identity_matrix() {
    Matrix m(4,4);
    for(size_t i = 0; i < 4; ++i){
        m.at(i,i) = 1;
    }
    return m;
}

Primitives::Matrix Primitives::Matrix::transpose() {
    Matrix m(height, width);
    for(size_t row = 0; row < height; ++row){
        for(size_t column = 0; column < width; ++column){
            m.at(row, column) = this->at(column, row);
        }
    }
    return m;
}

float Primitives::Matrix::determinant(Primitives::Matrix &mat) {
    if(mat.width == 2 && mat.height == 2){
        return mat.at(0,0) * mat.at(1,1) - mat.at(1,0) * mat.at(0,1);
    } else {
        throw "Matrix too large to find determinant";
    }
}

Primitives::Matrix Primitives::Matrix::sub_matrix(Primitives::Matrix &mat, size_t row, size_t column) {
    

}
