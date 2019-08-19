//
// Created by Rick Simon on 2019-08-05.
//

#ifndef TRACER_CHALLENGE_RAY_H
#define TRACER_CHALLENGE_RAY_H

#include <Tuple.h>
#include <memory>
#include <vector>
#include <tuple>
#include <set>
#include <Collision.h>

namespace Simulation {
    class Entity;
}
namespace Render {


    class Ray {

        Primitives::Tuple _data[2];

    public:
        Ray();

        Ray(Primitives::Tuple, Primitives::Tuple);

        Primitives::Tuple &origin();

        Primitives::Tuple &direction();

        Primitives::Tuple at(float);

        void cast(Simulation::Entity &);

        Render::Collision _collision;
    };
}

#endif //TRACER_CHALLENGE_RAY_H
