//
// Created by Rick Simon on 2018-12-18.
//

#ifndef TRACER_CHALLENGE_PROJECTILE_H
#define TRACER_CHALLENGE_PROJECTILE_H

#include "../../Primitives/Include/Tuple.h"

namespace Simulation {
    class Projectile {

        Primitives::Tuple position;
        Primitives::Tuple momentum;

    public:

        Projectile();

        Projectile(Primitives::Tuple, Primitives::Tuple);

        void changeMomentum(const Primitives::Tuple &);

        void setPosition(const Primitives::Tuple &);

        Primitives::Tuple getPosition();

        Primitives::Tuple getMomentum();


    };
}

#endif //TRACER_CHALLENGE_PROJECTILE_H
