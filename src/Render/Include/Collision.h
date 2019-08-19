//
// Created by Rick Simon on 2019-08-15.
//

#ifndef TRACER_CHALLENGE_COLLISION_H
#define TRACER_CHALLENGE_COLLISION_H

#include <Entity.h>
#include <vector>

namespace Render {


    struct Collision {
        std::vector<float> coords;
        Simulation::Entity *obj;
        Collision hit();

        Collision();

    };
}
#endif //TRACER_CHALLENGE_COLLISION_H
