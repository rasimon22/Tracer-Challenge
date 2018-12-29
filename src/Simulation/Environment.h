//
// Created by Rick Simon on 2018-12-18.
//

#ifndef TRACER_CHALLENGE_ENVIRONMENT_H
#define TRACER_CHALLENGE_ENVIRONMENT_H

#include "../Primitives/Tuple.h"
#include "Projectile.h"
#include <vector>

namespace Simulation {
    class Environment {

        Primitives::Tuple gravity;

        Primitives::Tuple wind;

    public:

        Environment();

        Environment(Primitives::Tuple, Primitives::Tuple);

        Primitives::Tuple getGravity();

        Primitives::Tuple getWind();

        void setGravity(const Primitives::Tuple&);

        void setWind(const Primitives::Tuple&);




    };
    Simulation::Projectile tick(Simulation::Environment&, Simulation::Projectile&);
}


#endif //TRACER_CHALLENGE_ENVIRONMENT_H
