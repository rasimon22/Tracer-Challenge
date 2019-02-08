//
// Created by Rick Simon on 2018-12-28.
//

#if 1

#include "catch.hpp"
#include <cmath>
#include "../src/Render/Color.h"
#include "../src/Render/Canvas.h"
#include <iostream>

TEST_CASE("Colors are RGB tuples")
{
    Render::Color c(1.0f, 2.0f, 3.0f);
    REQUIRE(c.red == 1.0f);
    REQUIRE(c.green == 2.0f);
    REQUIRE(c.blue == 3.0f);
}

TEST_CASE("Color equality")
{
    Render::Color c1(1.0f, 2.0f, 3.0f);
    Render::Color c2(1.0f, 2.0f, 3.0f);
    REQUIRE(c1 == c2);
}

TEST_CASE("Casting")
{
    Render::Color c1(1.0f, 2.0f, 3.0f);
    Primitives::Tuple t1(1.0f, 2.0f, 3.0f, 4.0f);
    REQUIRE(static_cast<Render::Color>(t1) == c1);
}

TEST_CASE("Adding Colors")
{
    Render::Color c1(1.0f, 2.0f, 3.0f);
    Render::Color c2(1.5f, 2.5f, 3.5f);
    REQUIRE(c1 + c2 == Primitives::Tuple(2.5f, 4.5f, 6.5f, 2.0f));
}
TEST_CASE("Subtracting Colors")
{
    Render::Color c1(1.0f, 2.0f, 3.0f);
    Render::Color c2(1.5f, 2.5f, 3.5f);
    REQUIRE(c2 - c1 == Primitives::Tuple(.5f, .5f, .5f, 0.0f));
}

TEST_CASE("Combining Colors (multiplication)")
{
    Render::Color c1(1.0f, 0.2f, 0.4f);
    Render::Color c2(0.9f, 1.0f, 0.1f);
    REQUIRE(c1 * c2 == Render::Color(0.9f, 0.2f, 0.04f));
}

TEST_CASE("Create Canvas of certain width")
{
    Render::Canvas c1(10, 20);
    REQUIRE(c1.shape() == Primitives::Tuple(10, 20, 0,0));
}

TEST_CASE("Writing Pixel to Canvas")
{
    Render::Canvas c1(100, 200);
    Render::Color red(255.0f,255.0f,100.0f);

    c1.at(2, 3) = red;

    REQUIRE(c1.at(2,3) == Render::Color(255.0f, 255.0f, 100.0f));
}

#endif
