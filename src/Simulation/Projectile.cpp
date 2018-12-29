//
// Created by Rick Simon on 2018-12-18.
//

#include "Projectile.h"

Simulation::Projectile::Projectile(){
    this -> position = Primitives::point(0.0f, 0.0f, 0.0f);
    this -> momentum = Primitives::vector(0.0f, 0.0f, 0.0f);
}
Simulation::Projectile::Projectile(Primitives::Tuple position, Primitives::Tuple momentum){
    this -> position = position;
    this -> momentum = momentum;
}

Primitives::Tuple Simulation::Projectile::getPosition() {
    return this -> position;
}

void Simulation::Projectile::changeMomentum(const Primitives::Tuple &a) {
   this -> momentum = this -> momentum + a;
}

void Simulation::Projectile::setPosition(const Primitives::Tuple &pos) {
    this -> position = pos;
}

Primitives::Tuple Simulation::Projectile::getMomentum() {
    return this -> momentum;
}

