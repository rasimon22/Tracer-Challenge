//
// Created by Rick Simon on 2018-12-18.
//

#include "Environment.h"
#include "Projectile.h"


Primitives::Tuple Simulation::Environment::getGravity(){
   return gravity;
}

Primitives::Tuple Simulation::Environment::getWind() {
   return wind;
}

void Simulation::Environment::setGravity(const Primitives::Tuple &grav) {
   gravity = grav;
}

void Simulation::Environment::setWind(const Primitives::Tuple &wind) {
   wind = wind;
}

Simulation::Environment::Environment() {
   gravity = Primitives::vector(0.0, 0.0, 0.0);
   wind = Primitives::vector(0.0, 0.0, 0.0);
}

Simulation::Environment::Environment(Primitives::Tuple g, Primitives::Tuple w) {
   gravity = g;
   wind = w;

}

Simulation::Projectile Simulation::tick(Simulation::Environment &env, Simulation::Projectile &proj) {
   //TODO:Refactor out unnecessary copies
   Primitives::Tuple position = proj.getPosition() + proj.getMomentum();
   Primitives::Tuple velocity = proj.getMomentum() + env.getWind() + env.getGravity();
   return Simulation::Projectile(position, velocity);
}

