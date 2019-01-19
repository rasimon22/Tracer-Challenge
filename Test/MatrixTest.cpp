//
// Created by Rick Simon on 2019-01-15.
//


#if 1

#include "catch.hpp"
#include "../src/Primitives/Tuple.h"
#include "../src/Primitives/Matrix.h"
#include <iostream>
#include <vector>
TEST_CASE("Constructors"){
    Primitives::Matrix m;
    m.at(1,1) = 4.0f;
    REQUIRE(Primitives::float_equal(m.at(1,1), 4.0f));
    Primitives::Matrix m2(m);
    REQUIRE(Primitives::float_equal(m.at(1,1), m2.at(1,1)));
    REQUIRE(&m.at(1,1) != &m2.at(1,1));

}
TEST_CASE("Matrix Construction"){
    std::vector<float> v;
    v.reserve(16);
    for(auto i = 0; i < 16; ++i){
        v.push_back(float(i));
    }
    Primitives::Matrix m3(v, 4, 4);
    for(auto i = 0; i < 4; ++i){
        for(auto j = 0; j < 4; ++j){
            REQUIRE(Primitives::float_equal(m3.at(j, i), float( 4 * i + j)));
        }
    }
}

TEST_CASE("Matrix Equality"){
    Primitives::Matrix m1;
    Primitives::Matrix m2;
    REQUIRE(m1 == m2);
    m2.at(1,1) = 10.0f;
    REQUIRE(!(m1 == m2));
}

TEST_CASE("Matrix Multiplication"){
    Primitives::Matrix m1(2, 2);
    Primitives::Matrix m2(2, 2);
    m1.at(0,0) = 1.0f;
    m1.at(1,0) = 2.0f;
    m1.at(0,1) = 3.0f;
    m1.at(1,1) = 4.0f;

    m2.at(0,0) = 2.0f;
    m2.at(1,0) = 0.0f;
    m2.at(0,1) = 1.0f;
    m2.at(1,1) = 2.0f;

    Primitives::Matrix result(2, 2);
    result.at(0,0) = 4.0f;
    result.at(1,0) = 4.0f;
    result.at(0,1) = 10.0f;
    result.at(1,1) = 8.0f;
    REQUIRE(m1 * m2 == result);
    Primitives::Matrix fail1(3,3);
    Primitives::Matrix fail2(4,4);

    //try catch to test for mismatched dimension exceptions
    try{
        fail1 * fail2;
        REQUIRE(false);
    } catch(...) {
        REQUIRE(true);
    }
}

TEST_CASE("Matrix Multiplication by Tuple") {
    Primitives::Matrix m1(4,4);
    Primitives::Tuple t1(1,2,3,1);

    m1.at(0,0) = 1;
    m1.at(1,0) = 2;
    m1.at(2,0) = 3;
    m1.at(3,0) = 4;

    m1.at(0,1) = 2;
    m1.at(1,1) = 4;
    m1.at(2,1) = 4;
    m1.at(3,1) = 2;

    m1.at(0,2) = 8;
    m1.at(1,2) = 6;
    m1.at(2,2) = 4;
    m1.at(3,2) = 1;

    m1.at(0,3) = 0;
    m1.at(1,3) = 0;
    m1.at(2,3) = 0;
    m1.at(3,3) = 1;

    Primitives::Matrix result(4,1);
    result.at(0,0) = 18;
    result.at(1,0) = 24;
    result.at(2,0) = 33;
    result.at(3,0) = 1;

    REQUIRE(m1 * t1 == result);

}

TEST_CASE("Identity Matrix"){
    Primitives::Tuple t1(1,2,3,1);
    REQUIRE(Primitives::Matrix::identity_matrix() * t1 == static_cast<Primitives::Matrix>(t1));
}

TEST_CASE("Matrix Transposition"){
    REQUIRE(Primitives::Matrix::identity_matrix().transpose() == Primitives::Matrix::identity_matrix());

    Primitives::Matrix a(4,4);
    Primitives::Matrix b(4,4);

    a.at(0,0) = 0;
    a.at(1,0) = 9;
    a.at(2,0) = 3;
    a.at(3,0) = 0;

    a.at(0,1) = 9;
    a.at(1,1) = 8;
    a.at(2,1) = 0;
    a.at(3,1) = 8;

    a.at(0,2) = 1;
    a.at(1,2) = 8;
    a.at(2,2) = 5;
    a.at(3,2) = 3;

    a.at(0,3) = 0;
    a.at(1,3) = 0;
    a.at(2,3) = 5;
    a.at(3,3) = 8;

    b.at(0,0) = 0;
    b.at(1,0) = 9;
    b.at(2,0) = 1;
    b.at(3,0) = 0;

    b.at(0,1) = 9;
    b.at(1,1) = 8;
    b.at(2,1) = 8;
    b.at(3,1) = 0;

    b.at(0,2) = 3;
    b.at(1,2) = 0;
    b.at(2,2) = 5;
    b.at(3,2) = 5;

    b.at(0,3) = 0;
    b.at(1,3) = 8;
    b.at(2,3) = 3;
    b.at(3,3) = 8;

    REQUIRE(a.transpose() == b);
}

TEST_CASE("Matrix Determinants") {
    Primitives::Matrix a(2,2);
    a.at(0, 0) = 1;
    a.at(1, 0) = 5;
    a.at(0, 1) = -3;
    a.at(1, 1) = 2;
    SECTION("2x2 Determinant") {
        REQUIRE(Primitives::Matrix::determinant(a) == 17);
    }
}

#endif