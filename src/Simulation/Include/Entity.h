//
// Created by Rick Simon on 2019-08-05.
//

#ifndef TRACER_CHALLENGE_ENTITY_H
#define TRACER_CHALLENGE_ENTITY_H
#include<Tuple.h>
namespace Simulation {
    class Entity {
    protected:
        Primitives::Tuple _position;
    public:
        Primitives::Tuple &position();
    };
}
#endif //TRACER_CHALLENGE_ENTITY_H
