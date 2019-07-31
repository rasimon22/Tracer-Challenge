//
// Created by rasimon on 7/24/19.
//
#include <dimension_error.h>
#include <Matrix.h>
#include <ostream>

namespace Primitives {
    namespace Exceptions {
        Primitives::Exceptions::DimensionError::DimensionError(Primitives::Matrix &lhs, Primitives::Matrix &rhs,
                std::ostream &stream): lhs(lhs), rhs(rhs), stream(stream) {

        }

        void Primitives::Exceptions::DimensionError::what() {
            stream << "Dimension Mismatch Error \n";
            lhs.print(stream);
            stream << "Does not match dimensions with \n";
            rhs.print(stream);
        }

    }

}

