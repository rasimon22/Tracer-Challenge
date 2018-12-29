//
// Created by Rick Simon on 2018-12-18.
//

#include "Environment.h"
#include "Projectile.h"


Primitives::Tuple Simulation::Environment::getGravity(){
   return this -> gravity;
}

Primitives::Tuple Simulation::Environment::getWind() {
   return this -> wind;
}

void Simulation::Environment::setGravity(const Primitives::Tuple &grav) {
   this -> gravity = grav;
}

void Simulation::Environment::setWind(const Primitives::Tuple &wind) {
   this -> wind = wind;
}

Simulation::Environment::Environment() {
   this -> gravity = Primitives::vector(0.0, 0.0, 0.0);
   this -> wind = Primitives::vector(0.0, 0.0, 0.0);
}

Simulation::Environment::Environment(Primitives::Tuple g, Primitives::Tuple w) {
   this -> gravity = g;
   this -> wind = w;

}

Simulation::Projectile Simulation::tick(Simulation::Environment &env, Simulation::Projectile &proj) {
   Primitives::Tuple position = proj.getPosition() + proj.getMomentum();
   Primitives::Tuple velocity = proj.getMomentum() + env.getWind() + env.getGravity();
   return Simulation::Projectile(position, velocity);
}

