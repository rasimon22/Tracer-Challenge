//
// Created by Rick Simon on 2019-01-15.
//

#ifndef TRACER_CHALLENGE_MATRIX_H
#define TRACER_CHALLENGE_MATRIX_H

#include <memory>
#include <vector>
#include <iostream>
#include "Tuple.h"
namespace Primitives {
    class Matrix {

    public:
        Matrix();
        Matrix(size_t, size_t);
        Matrix(const Matrix&);
        Matrix(Matrix&&);
        Matrix(std::vector<float>, size_t, size_t);
        Matrix(const float*, size_t, size_t);
        Matrix(Primitives::Tuple&);
        float& at(size_t, size_t);
        bool operator==(const Matrix&) const;
        bool operator!=(const Matrix&) const;
        Matrix operator*(Matrix&);
        Tuple operator*(Primitives::Tuple&);
        void print(std::ostream&);
        static Matrix identity_matrix();
        static Matrix translate(float, float, float);
        static Matrix scale(float, float, float);
        static Matrix rotate_x(double);
        static Matrix rotate_y(double);
        static Matrix rotate_z(double);
        Matrix transpose();
        static float determinant(Matrix&);
        Matrix sub_matrix(size_t, size_t);
        float matrix_minor(size_t, size_t);
        float cofactor(size_t, size_t);
        friend std::ostream& operator<<(std::ostream&, Matrix&);
        bool is_invertable();
        Matrix invert();
        Matrix& operator=(Matrix&&);




    private:
        std::unique_ptr<float[]> data;
        size_t height, width;
        float calculateCell(size_t, size_t, Matrix&, Matrix&);


    };

}


#endif //TRACER_CHALLENGE_MATRIX_H
