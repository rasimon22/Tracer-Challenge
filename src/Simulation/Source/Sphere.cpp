//
// Created by Rick Simon on 2019-08-05.
//
#include <Sphere.h>
#include <Tuple.h>
#include <Ray.h>
#include <cmath>

Simulation::Sphere::Sphere() {
  _position = Primitives::point(0, 0, 0);
}

void Simulation::Sphere::collide(Render::Ray &ray) {
  Primitives::Tuple obj_to_vec = ray.origin() - this->position();
  float a = Primitives::dot_product(ray.direction(), ray.direction());
  float b = 2 * Primitives::dot_product(ray.direction(), obj_to_vec);
  float c = Primitives::dot_product(obj_to_vec, obj_to_vec) - 1;
  auto descriminant = pow(b, 2) - (4 * a * c);
  if (descriminant < 0) {
    return;
  } else {
    ray._collision.obj = this;
    ray._collision.coords.push_back(float((-b - pow(descriminant, .5)) / 2 * a));
    ray._collision.coords.push_back(float((-b + pow(descriminant, .5)) / 2 * a));
  }

}

