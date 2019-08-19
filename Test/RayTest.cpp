//
// Created by Rick Simon on 2019-08-05.
//

#include "catch.hpp"
#include <Tuple.h>
#include <Ray.h>
#include <Sphere.h>

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
    auto e = Simulation::Sphere();
    auto r = Render::Ray(point(0, 0, -5), vector(0, 0, 1));
    r.cast(e);
    REQUIRE(r._collision.coords.size() == 2);
    REQUIRE(r._collision.coords[0] == 4.0);
    REQUIRE(r._collision.coords[1] == 6.0);
    REQUIRE(r._collision.obj == &e);
    REQUIRE(r._collision.hit().coords[0] == 4.0);
    r._collision.coords.clear();
    r._collision.obj = nullptr;
    r.origin() = point(0, 1, -5);
    r.cast(e);
    REQUIRE(r._collision.coords.size() == 2);
    REQUIRE(r._collision.obj == &e);
    r._collision.coords.clear();
    r._collision.obj = nullptr;
    r.origin() = point(0, 0, 0);
    r.cast(e);
    REQUIRE(r._collision.coords.size() == 2);
    REQUIRE(r._collision.obj == &e);
    REQUIRE(r._collision.hit().coords[0] == 1.0);
    r._collision.coords.clear();
    r._collision.obj = nullptr;
    r.origin() = point(0, 0, 5);
    r.cast(e);
    REQUIRE(r._collision.coords.size() == 2);
    REQUIRE(r._collision.obj == &e);
    r._collision.coords.clear();
    r._collision.obj = nullptr;
    r.origin() = point(0, 2, -5);
    r.cast(e);
    REQUIRE(r._collision.coords.size() == 0);
    REQUIRE(r._collision.hit().coords[0] == std::numeric_limits<float>::max());
    REQUIRE(r._collision.obj == nullptr);
  }
}