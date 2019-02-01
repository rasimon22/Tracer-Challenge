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

Primitives::Matrix::Matrix(const float *in, size_t x, size_t y):width(x), height(y),
data(std::make_unique<float[]>(x * y)) {
    for(auto i = 0; i < x * y; ++i){
        data[i] = in[i];
    }
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

Primitives::Matrix::Matrix(Primitives::Matrix &&rhs):width(std::move(rhs.width)), height(std::move(rhs.height)),
data(std::move(rhs.data)){

}

bool Primitives::Matrix::operator==(const Primitives::Matrix& rhs) const{
    if(height == rhs.height && width == rhs.width){
        float* l_ptr = &data[0];
        float* r_ptr = &rhs.data[0];
        for(size_t i = 0; i < width * height; ++i){
            if(!Primitives::float_equal(*l_ptr, * r_ptr)) return false;
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
}




