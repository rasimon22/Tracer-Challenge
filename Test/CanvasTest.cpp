//
// Created by Rick Simon on 2018-12-28.
//

#if 1

#include "catch.hpp"
#include <cmath>
#include "../src/Canvas/Color.h"

TEST_CASE("Colors are RGB tuples")
{
    Canvas::Color c(1.0f, 2.0f, 3.0f);
    REQUIRE(c.red == 1.0f);
    REQUIRE(c.green == 2.0f);
    REQUIRE(c.blue == 3.0f);
}

TEST_CASE("Color equality")
{
    Canvas::Color c1(1.0f, 2.0f, 3.0f);
    Canvas::Color c2(1.0f, 2.0f, 3.0f);
    REQUIRE(c1 == c2);
}

TEST_CASE("Casting")
{
    Canvas::Color c1(1.0f, 2.0f, 3.0f);
    Primitives::Tuple t1(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(static_cast<Canvas::Color>(t1) == c1);
}

TEST_CASE("Adding Colors")
{
    Canvas::Color c1(1.0f, 2.0f, 3.0f);
    Canvas::Color c2(1.5f, 2.5f, 3.5f);
    REQUIRE(c1 + c2 == Primitives::Tuple(2.5f, 4.5f, 6.5f, 2.0f));
}
TEST_CASE("Subtracting Colors")
{
    Canvas::Color c1(1.0f, 2.0f, 3.0f);
    Canvas::Color c2(1.5f, 2.5f, 3.5f);
    REQUIRE(c2 - c1 == Primitives::Tuple(.5f, .5f, .5f, 0.0f));
}

TEST_CASE("Combining Colors (multiplication)")
{
    Canvas::Color c1(1.0f, 0.2f, 0.4f);
    Canvas::Color c2(0.9f, 1.0f, 0.1f);
    REQUIRE(c1 * c2 == Canvas::Color(0.9f, 0.2f, 0.04f));
}


#endif
