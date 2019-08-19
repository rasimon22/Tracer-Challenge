//
// Created by Rick Simon on 2019-08-15.
//
#include <Collision.h>
#include <limits>

Render::Collision::Collision() {
  obj = nullptr;
}

Render::Collision Render::Collision::hit() {
  float min = std::numeric_limits<float>::max();
  for (auto f : coords) {
    if (f < min && f >= 0) min = f;
  }
  auto c = Collision();

  c.coords.push_back(min);
  c.obj = obj;

  return c;
}
