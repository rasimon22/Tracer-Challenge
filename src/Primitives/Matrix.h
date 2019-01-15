//
// Created by Rick Simon on 2019-01-15.
//

#ifndef TRACER_CHALLENGE_MATRIX_H
#define TRACER_CHALLENGE_MATRIX_H

#include <memory>
#include <vector>
namespace Primitives {
    class Matrix {

    public:
        Matrix();
        Matrix(size_t, size_t);
        Matrix(const Matrix&);
        Matrix(std::vector<float>, size_t, size_t);
        float& at(size_t, size_t);

    private:
        std::unique_ptr<float[]> data;
        size_t height, width;


    };
}


#endif //TRACER_CHALLENGE_MATRIX_H
