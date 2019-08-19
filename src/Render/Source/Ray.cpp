//
// Created by Rick Simon on 2019-08-05.
//

#include <Ray.h>
#include <cmath>
#include <Sphere.h>
#include <Collision.h>

Render::Ray::Ray() {
  _data[0] = Primitives::point(0, 0, 0);
  _data[1] = Primitives::vector(0, 0, 0);
}

Render::Ray::Ray(Primitives::Tuple origin, Primitives::Tuple direction) {
  _data[0] = origin;
  _data[1] = direction;
}

Primitives::Tuple &Render::Ray::origin() {
  return _data[0];
}

Primitives::Tuple &Render::Ray::direction() {
  return _data[1];
}

Primitives::Tuple Render::Ray::at(float steps) {
  return origin() + (direction() * steps);
}

void Render::Ray::cast(Simulation::Entity &obj) {
  obj.collide(*this);

}



