//
// Created by Rick Simon on 2019-01-15.
//

#include "catch.hpp"
#include <Tuple.h>
#include <Matrix.h>
#include <iostream>
#include <vector>
#include <exception>
#include <cmath>

#define PI 3.141592634

TEST_CASE("Constructors") {
  Primitives::Matrix m;
  m.at(1, 1) = 4.0f;
  REQUIRE(Primitives::float_equal(m.at(1, 1), 4.0f));
  Primitives::Matrix m2(m);
  REQUIRE(Primitives::float_equal(m.at(1, 1), m2.at(1, 1)));
  REQUIRE(&m.at(1, 1) != &m2.at(1, 1));

}

TEST_CASE("Matrix Construction") {
  std::vector<float> v;
  v.reserve(16);
  for (auto i = 0; i < 16; ++i) {
    v.push_back(float(i));
  }
  Primitives::Matrix m3(v, 4, 4);
  for (auto i = 0; i < 4; ++i) {
    for (auto j = 0; j < 4; ++j) {
      REQUIRE(Primitives::float_equal(m3.at(j, i), float(4 * i + j)));
    }
  }
}

TEST_CASE("Construction From const array of floats") {
  float dat[16];
  for (auto i = 0; i < 16; ++i) {
    dat[i] = i;
  }
  Primitives::Matrix constM(dat, 4, 4);

  REQUIRE(constM.at(0, 0) == 0);
  REQUIRE(constM.at(3, 3) == 15);

}

TEST_CASE("Matrix Equality") {
  Primitives::Matrix m1;
  Primitives::Matrix m2;
  REQUIRE(m1 == m2);
  m2.at(1, 1) = 10.0f;
  REQUIRE(!(m1 == m2));
}

TEST_CASE("Matrix Multiplication") {
  Primitives::Matrix m1({1.0f, 2.0f, 3.0f, 4.0f}, 2, 2);
  Primitives::Matrix m2({2.0f, 0.0f, 1.0f, 2.0f}, 2, 2);
  Primitives::Matrix result({4.0f, 4.0f, 10.0f, 8.0f}, 2, 2);
  REQUIRE(m1 * m2 == result);
  Primitives::Matrix fail1(3, 3);
  Primitives::Matrix fail2(4, 4);

//    try catch to test for mismatched dimension exceptions

  REQUIRE_THROWS(fail1 * fail2);
}

TEST_CASE("Matrix Multiplication by Tuple") {
  Primitives::Matrix m1({1, 2, 3, 4, 2, 4, 4, 2, 8, 6, 4, 1, 0, 0, 0, 1}, 4, 4);
  Primitives::Tuple t1(1, 2, 3, 1);

  Primitives::Tuple result(18, 24, 33, 1);

  REQUIRE(m1 * t1 == result);

}

TEST_CASE("Identity Matrix") {
  Primitives::Tuple t1(1, 2, 3, 1);
  REQUIRE(Primitives::Matrix::identity_matrix() * t1 == t1);
}

TEST_CASE("Matrix Transposition") {
  REQUIRE(Primitives::Matrix::identity_matrix().transpose() == Primitives::Matrix::identity_matrix());

  Primitives::Matrix a({0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8}, 4, 4);

  Primitives::Matrix b({0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8}, 4, 4);

  REQUIRE(a.transpose() == b);
}

TEST_CASE("Matrix Determinants") {
  Primitives::Matrix a({1, 5, -3, 2}, 2, 2);

  Primitives::Matrix l({-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1}, 4, 4);

  SECTION("2x2 Determinant") {
    REQUIRE(Primitives::Matrix::determinant(a) == 17);
  }
  SECTION("Sub matrices") {
    Primitives::Matrix b({1, 5, 6, -3, 2, 6, 6, 6, 6}, 3, 3);
    auto c = b.sub_matrix(2, 2);
    REQUIRE(c == a);
  }
  SECTION("Larger Submatricies") {

    Primitives::Matrix res({-6, 1, 6, -8, 8, 6, -7, -1, 1}, 3, 3);
    REQUIRE(l.sub_matrix(2, 1) == res);
  }
  Primitives::Matrix orig({3, 5, 0, 2, -1, -7, 6, -1, 5}, 3, 3);
  SECTION("Minor") {


    Primitives::Matrix submat = orig.sub_matrix(1, 0);

    REQUIRE(Primitives::Matrix::determinant(submat) == 25);

    REQUIRE(orig.matrix_minor(1, 0) == 25);

  }
  SECTION("Cofactors") {
    REQUIRE(orig.matrix_minor(0, 0) == -12);
    REQUIRE(orig.cofactor(0, 0) == -12);
    REQUIRE(orig.cofactor(1, 0) == -25);
  }
  SECTION("Larger Determinants") {
    Primitives::Matrix m3({1, 2, 6, -5, 8, -4, 2, 6, 4}, 3, 3);

    REQUIRE(m3.cofactor(0, 0) == 56);
    REQUIRE(m3.cofactor(0, 1) == 12);
    REQUIRE(m3.cofactor(0, 2) == -46);
    REQUIRE(Primitives::Matrix::determinant(m3) == -196);
    Primitives::Matrix m4({-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9}, 4, 4);
    REQUIRE(m4.cofactor(0, 0) == 690);
    REQUIRE(m4.cofactor(0, 1) == 447);
    REQUIRE(m4.cofactor(0, 2) == 210);
    REQUIRE(m4.cofactor(0, 3) == 51);
    REQUIRE(Primitives::Matrix::determinant(m4) == -4071);

  }
}

TEST_CASE("Matrix Inversion") {
  SECTION("Matrix Is Invertable") {
    Primitives::Matrix m1({6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6}, 4, 4);
    REQUIRE(m1.is_invertable());

    Primitives::Matrix m2({-4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0}, 4, 4);
    REQUIRE_FALSE(m2.is_invertable());
  }

  SECTION("Invert Matrix Tests") {
    Primitives::Matrix a({-5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4}, 4, 4);
    Primitives::Matrix b(a.invert());
    REQUIRE(Primitives::Matrix::determinant(a) == 532);
    REQUIRE(a.cofactor(2, 3) == -160);
    REQUIRE(Primitives::float_equal(b.at(2, 3), -0.30075f));
    REQUIRE(a.cofactor(3, 2) == 105);
    REQUIRE(Primitives::float_equal(b.at(3, 2), 0.19737f));
    Primitives::Matrix testMat(
            {0.218045, 0.451128, 0.240602, -0.0451128, -0.808271, -1.45677, -0.443609, 0.520677, -0.0789474, -0.223684,
             -0.0526316, 0.197368, -0.522556, -0.81391, -0.300752, 0.306391}, 4, 4);
    REQUIRE(b == testMat);
  }

  SECTION("Multiply by inverse matrices") {
    Primitives::Matrix _a({3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1}, 4, 4);
    Primitives::Matrix _b({8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5}, 4, 4);
    Primitives::Matrix _c(_a * _b);
    Primitives::Matrix _inv(_b.invert());
    REQUIRE(_c * _inv == _a);
  }
}

TEST_CASE("Scaling Matrices") {
  SECTION("Scaling a point") {
    auto transform = Primitives::Matrix::scale_matrix(2, 3, 4);
    auto p = Primitives::point(-4, 6, 8);
    REQUIRE(transform * p == Primitives::point(-8, 18, 32));
  }
  SECTION("Scaling a vector") {
    auto transform = Primitives::Matrix::scale_matrix(2, 3, 4);
    auto v = Primitives::vector(-4, 6, 8);
    REQUIRE(transform * v == Primitives::vector(-8, 18, 32));
  }
  SECTION("Multiplying vector by inverse scaling matrix") {
    auto transform = Primitives::Matrix::scale_matrix(2, 3, 4);
    auto inv = transform.invert();
    auto v = Primitives::vector(-4, 6, 8);
    REQUIRE(inv * v == Primitives::vector(-2, 2, 2));
  }
}

TEST_CASE("Rotation Matrices") {
  SECTION("Rotating about the X axis") {
    auto p = Primitives::point(0, 1, 0);
    auto half_quarter = Primitives::Matrix::rotate_x_matrix(PI / 4);
    auto full_quarter = Primitives::Matrix::rotate_x_matrix(PI);
    REQUIRE(half_quarter * p == Primitives::point(0, pow(2, .5) / 2, pow(2, .5) / 2));
    REQUIRE(Primitives::point(0, -1, 0) == full_quarter * p);
    REQUIRE(half_quarter.invert() * p == Primitives::point(0, pow(2, .5) / 2, -pow(2, .5) / 2));

  }

  SECTION("Rotating about the Y axis") {
    auto p = Primitives::point(1, 0, 0);
    auto half = Primitives::Matrix::rotate_y_matrix(PI);
    auto half_quarter = Primitives::Matrix::rotate_y_matrix(-PI / 4);
    REQUIRE(half * p == Primitives::point(-1, 0, 0));
    REQUIRE(half_quarter * p == Primitives::point(pow(2, .5) / 2, 0, pow(2, .5) / 2));
  }

  SECTION("Rotating about the Z axis") {
    auto p = Primitives::point(0, 1, 0);
    auto half_quarter = Primitives::Matrix::rotate_z_matrix(PI / 4);
    auto full_quarter = Primitives::Matrix::rotate_z_matrix(PI / 2);
    REQUIRE(half_quarter * p == Primitives::point(-pow(2, .5) / 2, pow(2, .5) / 2, 0));
    REQUIRE(full_quarter * p == Primitives::point(-1, 0, 0));
  }
}

TEST_CASE("Shearing Matrices") {
  SECTION("Test Shearing") {
    auto t = Primitives::Matrix::shear_matrix(1, 0, 0, 0, 0, 0);
    auto p = Primitives::point(2, 3, 4);
    REQUIRE(t * p == Primitives::point(5, 3, 4));
    t = Primitives::Matrix::shear_matrix(0, 1, 0, 0, 0, 0);
    REQUIRE(t * p == Primitives::point(6, 3, 4));
    t = Primitives::Matrix::shear_matrix(0, 0, 1, 0, 0, 0);
    REQUIRE(t * p == Primitives::point(2, 5, 4));
    t = Primitives::Matrix::shear_matrix(0, 0, 0, 1, 0, 0);
    REQUIRE(t * p == Primitives::point(2, 7, 4));
    t = Primitives::Matrix::shear_matrix(0, 0, 0, 0, 1, 0);
    REQUIRE(t * p == Primitives::point(2, 3, 6));
    t = Primitives::Matrix::shear_matrix(0, 0, 0, 0, 0, 1);
    REQUIRE(t * p == Primitives::point(2, 3, 7));
  }
}

TEST_CASE("Fluid API testing") {
  SECTION("Fluid Translation") {
    auto p = Primitives::point(0, 0, 0);
    auto m = Primitives::Matrix::identity_matrix();
    m.translate(1, 1, 1).translate(-1, -1, -1).translate(1, 1, 1);
    REQUIRE(m * p == Primitives::point(1, 1, 1));
  }
  SECTION("Fluid Scaling") {
    auto p = Primitives::point(-4, 6, 8);
    auto m = Primitives::Matrix::identity_matrix();
    m.scale(2, 3, 4).scale(-1, 1, 1);
    REQUIRE(m * p == Primitives::point(8, 18, 32));
  }
  SECTION("Fluid rotation") {
    auto p = Primitives::point(1, 0, 0);
    auto m = Primitives::Matrix::identity_matrix();
    m.rotate_z(PI / 2).rotate_x(PI / 2).rotate_y(PI / 2);
    REQUIRE(m * p == Primitives::point(1, 0, 0));
  }
}

