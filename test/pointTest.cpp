// A test case for all public methods of the Point class

// Custom class header file imports
#include "Point.h"

// Import testing framework
#include "catch.hpp"

TEST_CASE("point test", "[point]")
{
    Point p0;
    REQUIRE(p0.getX() == 0);
    REQUIRE(p0.getY() == 0);
    Point p1(100, -2223);
    REQUIRE(p1.getX() == 100);
    REQUIRE(p1.getY() == -2223);
    REQUIRE(p0.getX() != p1.getX());
    REQUIRE(p0.getY() != p1.getY());
    REQUIRE(p0.same(p1) == false);
    Point p2(p1.getX(), p1.getY());
    REQUIRE(p2.same(p1) == true);
    REQUIRE(p2.same(p0) == false);
}
