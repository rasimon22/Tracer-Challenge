//
// Created by Rick Simon on 2019-08-05.
//

#ifndef TRACER_CHALLENGE_RAY_H
#define TRACER_CHALLENGE_RAY_H
#include <../../Primitives/Include/Tuple.h>
#include <memory>

namespace Render {
    class Ray {

        Primitives::Tuple _data[2];

    public:
        Ray();
        Ray(Primitives::Tuple, Primitives::Tuple);
        Primitives::Tuple &origin();
        Primitives::Tuple &direction();
        Primitives::Tuple at(float);


    };
}

#endif //TRACER_CHALLENGE_RAY_H
