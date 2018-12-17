//
// Created by Rick Simon on 2018-12-17.
//
#if 1

#include "catch.hpp"
#include "../src/Primitives/Tuple.h"


TEST_CASE("A tuple with w=1.0 is a point")
{
    Primitives::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
    REQUIRE(a.x == 4.3f);
    REQUIRE(a.y == -04.2f);
    REQUIRE(a.z == 3.1f);
    REQUIRE(a.w == 1.0f);
    REQUIRE(a.type() == Primitives::Tuple::Type::Point);
    REQUIRE(a.type() != Primitives::Tuple::Type::Vector);
}
TEST_CASE("A tuple with w=0.0 is a vector")
{
    Primitives::Tuple a(4.3f, -4.2f, 3.1f, 0.0f);
    REQUIRE(a.x == 4.3f);
    REQUIRE(a.y == -4.2f);
    REQUIRE(a.z == 3.1f);
    REQUIRE(a.w == 0.0f);
    REQUIRE(a.type() == Primitives::Tuple::Type::Vector);
    REQUIRE(a.type() != Primitives::Tuple::Type::Point);
}

TEST_CASE("Tuples with same coordinates are equal")
{
    Primitives::Tuple a(4.3f, -4.2f, 3.1f, 1.0f);
    Primitives::Tuple b(4.30001f, -4.200001f, 3.100000001f, 1.0f);
    Primitives::Tuple c(6.0f, -4.2f, 3.1f, 1.0f);
    REQUIRE((a == b));
    REQUIRE_FALSE(a == c);
}

TEST_CASE("vector() creates tuple with w = 0")
{
    Primitives::Tuple a = Primitives::vector(1.0f, 2.0f, 3.0f);
    Primitives::Tuple b(1.0f, 2.0f, 3.0f, 0.0f);
    REQUIRE((a == b));
}

TEST_CASE("point() creates tuple with w = 0")
{
    Primitives::Tuple a = Primitives::point(1.0f, 2.0f, 3.0f);
    Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
    REQUIRE((a == b));
}

TEST_CASE("Adding two tuples")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple c = a + b;
    Primitives::Tuple d(2.0f, 4.0f, 6.0f, 2.0f);
    REQUIRE(c==d);
}

TEST_CASE("Subtracting two tuples")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple c = a - b;
    Primitives::Tuple d(0.0f, 0.0f, 0.0f, 0.0f);
    REQUIRE(c==d);
}

TEST_CASE("Negation operator")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(-1.0f, -2.0f, -3.0f, -1.0f);
    REQUIRE(-a == b);
}

TEST_CASE("Multiplying by scalar")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
    REQUIRE(a * 2.0f == b);

}

TEST_CASE("In place scalar")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
    a *= 2.0f;
    REQUIRE(a == b);
}

TEST_CASE("Dividing by scalar")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
    REQUIRE(b / 2.0f == a);

}
TEST_CASE("In place scalar divide")
{
    Primitives::Tuple a(1.0f, 2.0f, 3.0f, 1.0f);
    Primitives::Tuple b(2.0f, 4.0f, 6.0f, 2.0f);
    b /= 2.0f;
    REQUIRE(b == a);
}
#endif

