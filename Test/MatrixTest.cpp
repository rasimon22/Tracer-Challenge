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

    Primitives::Matrix result(1,4);
    result.at(0,0) = 18;
    result.at(1,0) = 24;
    result.at(2,0) = 33;
    result.at(3,0) = 1;

}
#endif