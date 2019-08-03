//
// Created by Rick Simon on 2019-01-15.
//

#include "../Include/Matrix.h"
#include "../Include/Tuple.h"
#include <cstring>
#include <dimension_error.h>
#include <iostream>
#include <cmath>

Primitives::Matrix::Matrix(): width(4), height(4), data(std::make_unique<float[]>(16)) {
    std::memset(data.get(), 0, sizeof(float) * width * height);
}

float& Primitives::Matrix::at(size_t x, size_t y) {
    return data[y*width + x];
}

Primitives::Matrix::Matrix(size_t height, size_t width): width(width), height(height),
                                                         data(std::make_unique<float[]>(width*height)){
}

Primitives::Matrix::Matrix(const float *in, size_t x, size_t y):width(x), height(y),
data(std::make_unique<float[]>(x * y)) {
    for(auto i = 0; i < x * y; ++i){
        data[i] = in[i];
    }
}

//TODO:Refactor initialization out of I-list into self assignment check
Primitives::Matrix::Matrix(const Primitives::Matrix& rhs) {
    if(&rhs != this) {
        width = rhs.width;
        height = rhs.height;
        data = std::make_unique<float[]>(rhs.width * rhs.height);
        for (size_t i = 0; i < width * height; ++i) {
            data[i] = rhs.data[i];
        }
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

Primitives::Matrix::Matrix(Primitives::Matrix &&rhs):width(std::move(rhs.width)), height(std::move(rhs.height)),
data(std::move(rhs.data)){

}

bool Primitives::Matrix::operator==(const Primitives::Matrix& rhs) const{
    if(height == rhs.height && width == rhs.width){
        float* l_ptr = data.get();
        float* r_ptr = rhs.data.get();
        for(size_t i = 0; i < width * height; ++i){
            if(!Primitives::float_equal(*l_ptr, * r_ptr)) return false;
            ++l_ptr;
            ++r_ptr;
        }
        return true;
    }
    return false;
}

bool Primitives::Matrix::operator!=(const Primitives::Matrix& rhs) const {
   return !(*this == rhs);
}

Primitives::Matrix Primitives::Matrix::operator*(Primitives::Matrix &rhs){
    if(width != rhs.height){
        throw Primitives::Exceptions::DimensionError(*this, rhs, std::cerr);
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
        for(size_t j = 0; j < width; ++j){
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

Primitives::Tuple Primitives::Matrix::operator*(Primitives::Tuple &rhs) {
    //TODO: Refactor String Throw into Exception Type
    float res[4];
    if(this->width != 4 || this->height != 4) throw "Dimension Mismatch";
    for(size_t i = 0; i < 4; ++i) {
        res[i] = this->at(0, i) * rhs.x +
                 this->at(1, i) * rhs.y +
                 this->at(2, i) * rhs.z +
                 this->at(3,i) * rhs.w;
    }
    return Tuple(res[0], res[1], res[2], res[3]);
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
    }
        float det = 0;
        for(size_t i = 0; i < mat.width; ++i) {
            det += mat.at(i,0) * mat.cofactor(0,i);

        }
        return det;
}

Primitives::Matrix Primitives::Matrix::sub_matrix(size_t row, size_t column) {
    Primitives::Matrix m(this->width - 1, this->height - 1);
    for(size_t r = 0; r < m.height; ++r){
        for(size_t col = 0; col < m.width; ++col){
            if(r < row && col < column){
                m.at(col, r) = this->at(col, r);
            }
            if(r >= row || col >= column){
                size_t x_coord, y_coord;

                r >= row ? y_coord = r + 1 : y_coord = r;
                col >= column ? x_coord = col + 1 : x_coord = col;
                m.at(col, r) = this->at(x_coord, y_coord);
            }
        }
    }
    return m;
}

float Primitives::Matrix::matrix_minor(size_t x, size_t y) {
    Matrix m(this->sub_matrix(x,y));
    return determinant(m);
}

float Primitives::Matrix::cofactor(size_t x, size_t y) {
    float ret;
    (x + y) % 2 == 0 ? ret = this->matrix_minor(x, y) : ret = (0 - this->matrix_minor(x,y));
    return ret;
}

std::ostream &Primitives::operator<<(std::ostream& os, Primitives::Matrix& rhs) {
    rhs.print(os);
    return os;
}

bool Primitives::Matrix::is_invertable() {
    return Matrix::determinant(*this) != 0;
}

Primitives::Matrix Primitives::Matrix::invert() {
    Matrix inverted(4,4);

    for(auto rows = 0; rows < this -> height; ++rows){
        for(auto columns = 0; columns < this -> width; ++columns){
            inverted.at(columns, rows) = this -> cofactor(columns, rows);
        }
    }

    float det = Matrix::determinant(*this);

    for(auto rows = 0; rows < this -> height; ++rows){
        for(auto columns = 0; columns < this -> height; ++columns){
            inverted.at(columns,rows) /= det;
        }
    }

    return inverted;
}

Primitives::Matrix &Primitives::Matrix::operator=(Primitives::Matrix &&rhs) {
    width = std::move(rhs.width);
    height = std::move(rhs.height);
    data = std::move(rhs.data);
    return *this;
}

Primitives::Matrix Primitives::Matrix::translation_matrix(float x, float y, float z) {
    auto m = Primitives::Matrix::identity_matrix();
    m.at(3,0) = x;
    m.at(3,1) = y;
    m.at(3,2) = z;
    return m;
}

Primitives::Matrix Primitives::Matrix::scale_matrix(float x, float y, float z) {
    auto m = Primitives::Matrix::identity_matrix();
    m.at(0,0) = x;
    m.at(1,1) = y;
    m.at(2,2) = z;
    return m;
}

Primitives::Matrix Primitives::Matrix::rotate_x_matrix(double rad) {
   auto m = Primitives::Matrix::identity_matrix();
   m.at(1,1) = cos(rad);
   m.at(2,1) = -sin(rad);
   m.at(1,2) = sin(rad);
   m.at(2,2) = cos(rad);
   return m;
}

Primitives::Matrix Primitives::Matrix::rotate_y_matrix(double rad) {
    auto m = Primitives::Matrix::identity_matrix();
    m.at(0, 0) = cos(rad);
    m.at(2,0) = sin(rad);
    m.at(0,2) = -sin(rad);
    m.at(2,2) = cos(rad);
    return m;
}

Primitives::Matrix Primitives::Matrix::rotate_z_matrix(double rad) {
    auto m = Primitives::Matrix::identity_matrix();
    m.at(0,0) = cos(rad);
    m.at(1,0) = -sin(rad);
    m.at(0,1) = sin(rad);
    m.at(1,1) = cos(rad);
    return m;
}

Primitives::Matrix Primitives::Matrix::shear_matrix(float xy, float xz, float yx, float yz, float zx, float zy) {
    auto m = Primitives::Matrix::identity_matrix();
    m.at(1, 0) = xy;
    m.at(2, 0) = xz;
    m.at(0, 1) = yx;
    m.at(2, 1) = yz;
    m.at(0, 2) = zx;
    m.at(1, 2) = zy;
    return m;
}
Primitives::Matrix& Primitives::Matrix::translate(float x, float y, float z) {
    auto m = Primitives::Matrix::translation_matrix(x, y ,z);
    *this = m * *this;
    return *this;
}

Primitives::Matrix& Primitives::Matrix::scale(float x, float y, float z) {
    auto m = Primitives::Matrix::scale_matrix(x, y, z);
    *this = m * *this;
    return *this;
}

Primitives::Matrix& Primitives::Matrix::rotate_x(double rad) {
    auto m = Primitives::Matrix::rotate_x_matrix(rad);
    *this = m * *this;
    return *this;
}

Primitives::Matrix &Primitives::Matrix::rotate_y(double rad) {
    auto m = Primitives::Matrix::rotate_y_matrix(rad);
    *this = m * *this;
    return *this;
}

Primitives::Matrix &Primitives::Matrix::rotate_z(double rad) {
    auto m = Primitives::Matrix::rotate_z_matrix(rad);
    *this = m * *this;
    return *this;
}

Primitives::Matrix &Primitives::Matrix::shear(float xy, float xz, float yx, float yz, float zx, float zy) {
    auto m = Primitives::Matrix::shear_matrix(xy, xz, yx, yz, zx, zy);
    *this = m * *this;
    return *this;
}




