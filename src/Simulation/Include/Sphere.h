//
// Created by Rick Simon on 2019-08-05.
//

#ifndef TRACER_CHALLENGE_SPHERE_H
#define TRACER_CHALLENGE_SPHERE_H

#include <Entity.h>
#include <Tuple.h>

namespace Simulation {
    class Sphere : public Simulation::Entity {
    public:
        Sphere();

        void collide(Render::Ray &);
    };
}

#endif //TRACER_CHALLENGE_SPHERE_H
