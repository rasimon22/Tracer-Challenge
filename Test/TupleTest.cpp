//
// Created by Rick Simon on 2018-12-17.
//

#include "catch.hpp"
#include <cmath>
#include <Tuple.h>


TEST_CASE("A tuple with w=1.0 is a point") {
  Primitives::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
  REQUIRE(a.x == 4.3f);
  REQUIRE(a.y == -04.2f);
  REQUIRE(a.z == 3.1f);
  REQUIRE(a.w == 1.0f);
  REQUIRE(a.type() == Primitives::Tuple::Type::Point);
  REQUIRE(a.type() != Primitives::Tuple::Type::Vector);
}

TEST_CASE("A tuple with w=0.0 is a vector") {
  Primitives::Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
  REQUIRE(a.x == 4.3f);
  REQUIRE(a.y == -4.2f);
  REQUIRE(a.z == 3.1f);
  REQUIRE(a.w == 0.0f);
  REQUIRE(a.type() == Primitives::Tuple::Type::Vector);
  REQUIRE(a.type() != Primitives::Tuple::Type::Point);
}

TEST_CASE("Tuples with same coordinates are equal") {
  Primitives::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
  Primitives::Tuple b(4.30001f, -4.200001f, 3.100000001f, 1.0f);
  Primitives::Tuple c(6.0f, -4.2f, 3.1f, 1.0f);
  REQUIRE((a == b));
  REQUIRE_FALSE(a == c);
}

TEST_CASE("vector() creates tuple with w = 0") {
  Primitives::Tuple a = Primitives::vector(1.0f, 2.0f, 3.0f);
  Primitives::Tuple b(1.0f, 2.0f, 3.0f, 0.0f);
  REQUIRE((a == b));
}

TEST_CASE("point() creates tuple with w = 0") {
  Primitives::Tuple a = Primitives::point(1.0f, 2.0f, 3.0f);
  Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
  REQUIRE((a == b));
}

TEST_CASE("Adding two tuples") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple c = a + b;
  Primitives::Tuple d(2.0f, 4.0f, 6.0f, 2.0f);
  REQUIRE(c == d);
}

TEST_CASE("Subtracting two tuples") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple c = a - b;
  Primitives::Tuple d(0.0f, 0.0f, 0.0f, 0.0f);
  REQUIRE(c == d);
}

TEST_CASE("Negation operator") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(-1.0f, -2.0f, -3.0f, -1.0f);
  REQUIRE(-a == b);
}

TEST_CASE("Multiplying by scalar") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
  REQUIRE(a * 2.0f == b);

}

TEST_CASE("In place scalar") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
  a *= 2.0f;
  REQUIRE(a == b);
}

TEST_CASE("Dividing by scalar") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
  REQUIRE(b / 2.0f == a);

}

TEST_CASE("In place scalar divide") {
  Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
  Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
  b /= 2.0f;
  REQUIRE(b == a);
}

TEST_CASE("Magnitude Calculation") {
  SECTION("1 component magnitude") {
    Primitives::Tuple v = Primitives::vector(1.0f, 0.0f, 0.0f);
    REQUIRE(v.magnitude() == 1.0f);
  }

  SECTION("Multi component magnitude") {
    Primitives::Tuple v = Primitives::vector(1.0f, 2.0f, 3.0f);
    REQUIRE(.01 * v.magnitude() > v.magnitude() - sqrt(14.0f));
  }

  SECTION("Negative components") {
    Primitives::Tuple v = Primitives::vector(-1.0f, -2.0f, -3.0f);
    REQUIRE(.01 * v.magnitude() > v.magnitude() - sqrt(14.0f));
  }
}

TEST_CASE("Normalizing Vectors") {
  SECTION("Single component normalize") {
    Primitives::Tuple v = Primitives::vector(4.0f, 0.0f, 0.0f);
    REQUIRE(v.normalize() == Primitives::vector(1.0f, 0.0f, 0.0f));
    REQUIRE(v.normalize().magnitude() == 1.0f);
  }

  SECTION("Multi component normalize") {
    Primitives::Tuple v = Primitives::vector(1.0f, 2.0f, 3.0f);
    REQUIRE(v.normalize() == Primitives::vector(1.0 / sqrt(14), 2.0 / sqrt(14), 3.0 / sqrt(14)));
    REQUIRE(abs(v.normalize().magnitude() - 1.0f) < 0.001);
  }
}

TEST_CASE("Dot Product") {
  Primitives::Tuple a = Primitives::vector(1.0f, 2.0f, 3.0f);
  Primitives::Tuple b = Primitives::vector(2.0f, 3.0f, 4.0f);
  REQUIRE(Primitives::dot_product(a, b) == 20.0f);
}

TEST_CASE("Cross Product") {
  Primitives::Tuple a = Primitives::vector(1.0f, 2.0f, 3.0f);
  Primitives::Tuple b = Primitives::vector(2.0f, 3.0f, 4.0f);

  REQUIRE(Primitives::cross_product(a, b) == Primitives::vector(-1.0f, 2.0f, -1.0f));
  REQUIRE(Primitives::cross_product(b, a) == Primitives::vector(1.0f, -2.0f, 1.0f));
}

