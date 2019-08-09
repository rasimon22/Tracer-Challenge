//
// Created by rasimon on 7/24/19.
//
#ifndef TRACER_CHALLENGE_DIMENSION_ERROR_H
#define TRACER_CHALLENGE_DIMENSION_ERROR_H

#include <exception>
#include <Matrix.h>
#include <ostream>

namespace Primitives {
    namespace Exceptions {
        class DimensionError : public std::exception {
        private:
            std::vector<size_t> dimensions;
            Primitives::Matrix lhs, rhs;
            std::ostream &stream;
        public:
            DimensionError(Primitives::Matrix &, Primitives::Matrix &, std::ostream &);

            void what();
        };
    }
}

#endif //TRACER_CHALLENGE_DIMENSION_ERROR_H
