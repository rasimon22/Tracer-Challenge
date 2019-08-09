//
// Created by Rick Simon on 2019-02-07.
//

#include "catch.hpp"
#include "../src/Primitives/Include/Matrix.h"
#include "../src/Primitives/Include/Tuple.h"

TEST_CASE("Matrix Translation of A Tuple") {
  auto m = Primitives::Matrix::translation_matrix(5, -3, 2);
  auto t = Primitives::point(-3, 4, 5);
  auto result = Primitives::point(2, 1, 7);
  auto vec = Primitives::vector(-3, 4, 5);
  SECTION("Translation Transformation") {
    REQUIRE(m * t == result);
  }
  SECTION("Translation Inverse") {
    REQUIRE(m.invert() * result == t);
  }

  SECTION("Translation Does Not Affect Vectors") {
    REQUIRE(m * vec == vec);
  }
}

TEST_CASE("Matrix Scaling of A Tuple") {
  auto transform = Primitives::Matrix::scale_matrix(2, 3, 4);
  auto p = Primitives::point(-4, 6, 8);
  auto v = Primitives::vector(p);
  auto res = Primitives::Tuple(-8, 18, 32, 1);
  SECTION("Point Scales Positively") {
    REQUIRE(transform * p == Primitives::point(res));
  }
  SECTION("Require Vectors are also Scaled") {
    REQUIRE(transform * v == Primitives::vector(res));
  }
  SECTION("Require Scaling in Opposite Direction") {
    REQUIRE(transform.invert() * res == p);
  }
}

