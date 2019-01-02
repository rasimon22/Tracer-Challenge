//
// Created by Rick Simon on 2018-12-18.
//

#include "Projectile.h"

Simulation::Projectile::Projectile(){
    position = Primitives::point(0.0f, 0.0f, 0.0f);
    momentum = Primitives::vector(0.0f, 0.0f, 0.0f);
}
Simulation::Projectile::Projectile(Primitives::Tuple position, Primitives::Tuple momentum){
    position = position;
    momentum = momentum;
}

Primitives::Tuple Simulation::Projectile::getPosition() {
    return position;
}

void Simulation::Projectile::changeMomentum(const Primitives::Tuple &a) {
   momentum = momentum + a;
}

void Simulation::Projectile::setPosition(const Primitives::Tuple &pos) {
    position = pos;
}

Primitives::Tuple Simulation::Projectile::getMomentum() {
    return momentum;
}

