//
// Created by Rick Simon on 2019-01-15.
//

#ifndef TRACER_CHALLENGE_MATRIX_H
#define TRACER_CHALLENGE_MATRIX_H

#include <memory>
#include <vector>
#include "Tuple.h"
namespace Primitives {
    class Matrix {

    public:
        Matrix();
        Matrix(size_t, size_t);
        Matrix(const Matrix&);
        Matrix(std::vector<float>, size_t, size_t);
        float& at(size_t, size_t);
        bool operator==(const Matrix&) const;
        Matrix operator*(Matrix&);
        Matrix operator*(Primitives::Tuple&);

    private:
        std::unique_ptr<float[]> data;
        size_t height, width;
        float calculateCell(size_t, size_t, Matrix&, Matrix&);


    };
}


#endif //TRACER_CHALLENGE_MATRIX_H
