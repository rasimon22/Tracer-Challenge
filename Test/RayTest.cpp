//
// Created by Rick Simon on 2019-08-05.
//

#include "catch.hpp"
#include "../src/Primitives/Include/Tuple.h"
#include <../src/Render/Include/Ray.h>
#include <../src/Simulation/Include/Sphere.h>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

using Primitives::Tuple;
using Primitives::point;
using Primitives::vector;

TEST_CASE("Ray construction") {
  SECTION("Constructors Produce") {
    auto p = point(1, 2, 3);
    auto v = vector(4, 5, 6);
    Render::Ray r(p, v);

    REQUIRE(r.origin() == p);
    REQUIRE(r.direction() == v);
    REQUIRE(Render::Ray().direction() == vector(0, 0, 0));
    REQUIRE(Render::Ray().origin() == point(0, 0, 0));
  }

  SECTION("Position on ray") {
    auto r = Render::Ray(point(2, 3, 4), vector(1, 0, 0));
    REQUIRE(r.at(3) == point(5, 3, 4));
    REQUIRE(r.at(-3.5) == point(-1.5, 3, 4));
  }

  SECTION("Intersecting With Entities") {

  }
}