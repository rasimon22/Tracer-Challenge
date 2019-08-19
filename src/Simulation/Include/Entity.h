//
// Created by Rick Simon on 2019-08-05.
//

#ifndef TRACER_CHALLENGE_ENTITY_H
#define TRACER_CHALLENGE_ENTITY_H


#include <Tuple.h>

namespace Render {
    class Ray;
}
namespace Simulation {
    class Entity {
    protected:
        Primitives::Tuple _position;
    public:
        Primitives::Tuple &position();

        virtual void collide(Render::Ray &) = 0;
    };
}
#endif //TRACER_CHALLENGE_ENTITY_H
