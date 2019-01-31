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

TEST_CASE("Construction From const array of floats"){
    float dat[16];
    for(auto i = 0; i < 16; ++i){
        dat[i] = i;
    }
    Primitives::Matrix constM(dat, 4, 4);

    REQUIRE(constM.at(0,0) == 0);
    REQUIRE(constM.at(3,3) == 15);

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

    Primitives::Matrix l(4,4);
    l.at(0,0) = -6;
    l.at(1,0) = 1;
    l.at(2,0) = 1;
    l.at(3,0) = 6;

    l.at(0,1) = -8;
    l.at(1,1) = 5;
    l.at(2,1) = 8;
    l.at(3,1) = 6;

    l.at(0,2) = -1;
    l.at(1,2) = 0;
    l.at(2,2) = 8;
    l.at(3,2) = 2;

    l.at(0,3) = -7;
    l.at(1,3) = 1;
    l.at(2,3) = -1;
    l.at(3,3) = 1;

    SECTION("2x2 Determinant") {
        REQUIRE(Primitives::Matrix::determinant(a) == 17);
    }
    SECTION("Sub matrices"){
        Primitives::Matrix b(3,3);
        b.at(0, 0) = 1;
        b.at(1, 0) = 5;
        b.at(2, 0) = 6;

        b.at(0, 1) = -3;
        b.at(1, 1) = 2;
        b.at(2, 1) = 6;

        b.at(0, 2) = 6;
        b.at(1, 2) = 6;
        b.at(2, 2) = 6;
        auto c = b.sub_matrix(2,2);
        REQUIRE(c == a);
    }
    SECTION("Larger Submatricies"){

        Primitives::Matrix res(3,3);
        res.at(0,0) = -6;
        res.at(1,0) = 1;
        res.at(2,0) = 6;

        res.at(0,1) = -8;
        res.at(1,1) = 8;
        res.at(2,1) = 6;

        res.at(0,2) = -7;
        res.at(1,2) = -1;
        res.at(2,2) = 1;

        REQUIRE(l.sub_matrix(2,1) == res);
    }
    Primitives::Matrix orig(3,3);

    orig.at(0,0) = 3;
    orig.at(1,0) = 5;
    orig.at(2,0) = 0;

    orig.at(0,1) = 2;
    orig.at(1,1) = -1;
    orig.at(2,1) = -7;

    orig.at(0,2) = 6;
    orig.at(1,2) = -1;
    orig.at(2,2) = 5;
    SECTION("Minor"){


        Primitives::Matrix submat = orig.sub_matrix(1,0);

        REQUIRE(Primitives::Matrix::determinant(submat) == 25);

        REQUIRE(orig.matrix_minor(1,0) == 25);

    }
    SECTION("Cofactors"){
        REQUIRE(orig.matrix_minor(0,0) == -12);
        REQUIRE(orig.cofactor(0,0) == -12);
        REQUIRE(orig.cofactor(1,0) == -25);
    }
    SECTION("Larger Determinants") {
        float dat3[9] = {1, 2, 6,
                         -5, 8, -4,
                         2, 6, 4};
        Primitives::Matrix m3(dat3,3,3);

        REQUIRE(m3.cofactor(0,0) == 56);
        REQUIRE(m3.cofactor(0,1) == 12);
        REQUIRE(m3.cofactor(0,2) == -46);
        REQUIRE(Primitives::Matrix::determinant(m3) == -196);
        float data[16] = {-2, -8, 3, 5,
                          -3, 1, 7, 3,
                          1 ,2, -9, 6,
                          -6, 7, 7, -9};
        Primitives::Matrix m4(data,4,4);
        REQUIRE(m4.cofactor(0,0) == 690);
        REQUIRE(m4.cofactor(0,1) == 447);
        REQUIRE(m4.cofactor(0,2) == 210);
        REQUIRE(m4.cofactor(0,3) == 51);
        REQUIRE(Primitives::Matrix::determinant(m4) == -4071);


    }
}

#endif