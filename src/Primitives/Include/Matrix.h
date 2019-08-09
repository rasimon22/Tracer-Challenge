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

        Matrix(const Matrix &);

        Matrix(Matrix &&);

        Matrix(std::vector<float>, size_t, size_t);

        Matrix(const float *, size_t, size_t);

        Matrix(Primitives::Tuple &);

        float &at(size_t, size_t);

        bool operator==(const Matrix &) const;

        bool operator!=(const Matrix &) const;

        Matrix operator*(Matrix &);

        Tuple operator*(Primitives::Tuple &);

        void print(std::ostream &);

        static Matrix identity_matrix();

        static Matrix translation_matrix(float, float, float);

        static Matrix scale_matrix(float, float, float);

        static Matrix rotate_x_matrix(double);

        static Matrix rotate_y_matrix(double);

        static Matrix rotate_z_matrix(double);

        static Matrix shear_matrix(float, float, float, float, float, float);

        Matrix transpose();

        static float determinant(Matrix &);

        Matrix sub_matrix(size_t, size_t);

        float matrix_minor(size_t, size_t);

        float cofactor(size_t, size_t);

        friend std::ostream &operator<<(std::ostream &, Matrix &);

        bool is_invertable();

        Matrix invert();

        Matrix &operator=(Matrix &&);

        Matrix &translate(float, float, float);

        Matrix &scale(float, float, float);

        Matrix &rotate_x(double);

        Matrix &rotate_y(double);

        Matrix &rotate_z(double);

        Matrix &shear(float, float, float, float, float, float);


    private:
        std::unique_ptr<float[]> data;
        size_t height, width;

        float calculateCell(size_t, size_t, Matrix &, Matrix &);


    };

}

#endif //TRACER_CHALLENGE_MATRIX_H
