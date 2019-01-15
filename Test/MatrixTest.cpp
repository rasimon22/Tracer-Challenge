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
TEST_CASE("Vector Construction"){
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
#endif