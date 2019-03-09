// A test case for all public methods of the Snake class

// Custom class header file imports
#include "Point.h"
#include "Snake.h"

// Import testing framework
#include "catch.hpp"

TEST_CASE("snake test", "[snake]" )
{
    // Test Snake object constructor
    SECTION("snake init test")
    {
        auto initTest = [](int len)
                        {
                            bool e = false;
                            try
                            {
                                Snake s(len);
                                REQUIRE(s.length() == len);
                                REQUIRE(s.getDir() == EAST);
                                REQUIRE(s.alive());
                                for(int i = 0; i < len; i++)
                                {
                                    Point p = s.pntAt(i);
                                    REQUIRE(p.getX() == p.getY() + i);
                                }
                                Point head = s.pntAt((int)s.length() - 1);
                                Point next(head.getX() + 1, head.getY());
                                REQUIRE(next.same(s.getNext()));
                            }
                            catch(...)
                            {
                                e = true;
                            }
                            if(len <= 0) REQUIRE(e); else REQUIRE(!e);
                        };

        initTest(5);
        initTest(22);
        initTest(0);
        initTest(400);
        initTest(-1);
        initTest(-999);
    }

    // Test the 'alive' and 'kill' methods
    SECTION("snake life test")
    {
        Snake s(4);
        REQUIRE(s.alive());
        s.kill();
        REQUIRE(s.alive() == false);
        s.kill();
        REQUIRE(s.alive() == false);
    }

    // Test getting and setting the snake direction
    SECTION("snake dir test")
    {
        auto testSetDir = [](Snake& s, enum direction d)
                          {
                              REQUIRE(s.getDir() != d);
                              s.setDir(d);
                              REQUIRE(s.getDir() == d);
                          };

        Snake s(7);
        REQUIRE(s.getDir() == EAST);
        REQUIRE(s.getDir() == EAST);
        testSetDir(s, NORTH);
        testSetDir(s, SOUTH);
        testSetDir(s, WEST);
        testSetDir(s, EAST);
    }

    // Test getting points out of the Snake object
    SECTION("snake pntAt test")
    {
        auto pntAtEx = [](Snake& s, int i)
                       {
                           bool e = false;
                           try
                           {
                               s.pntAt(i);
                           }
                           catch(...)
                           {
                               e = true;
                           }
                           return e;
                       };

        int sLen = 9;
        Snake s(sLen);
        for(int i = 0; i < sLen; i++)
        {
            REQUIRE(!pntAtEx(s, i));
        }
        REQUIRE(pntAtEx(s, -1));
        REQUIRE(pntAtEx(s, -25));
        REQUIRE(pntAtEx(s, -999));
        REQUIRE(pntAtEx(s, sLen));
        REQUIRE(pntAtEx(s, 42));
        REQUIRE(pntAtEx(s, 999));
    }

    // Test getting the next location the snake will advance to
    SECTION("snake next test")
    {
        auto checkNext = [](Snake& s, int xOffset, int yOffset)
                         {
                             Point p = s.pntAt(s.length() - 1);
                             Point next(p.getX() + xOffset, p.getY() + yOffset);
                             REQUIRE(next.same(s.getNext()));
                         };

        Snake s(14);
        REQUIRE(s.getDir() == EAST);
        s.setDir(NORTH);
        REQUIRE(s.getDir() == NORTH);
        checkNext(s, 0, -1);
        s.setDir(SOUTH);
        checkNext(s, 0, 1);
        s.setDir(WEST);
        checkNext(s, -1, 0);
        s.setDir(EAST);
        checkNext(s, 1, 0);
    }

    // Test moving the snake forward to a new point
    SECTION("snake move test")
    {
        auto testMove = [](Snake& s)
                        {
                            int sLen = s.length();
                            enum direction dir = s.getDir();
                            Point next = s.getNext();
                            Point oldTail = s.pntAt(0);
                            Point oldHead = s.pntAt(s.length() - 1);
                            s.move();
                            REQUIRE(s.length() == sLen);
                            REQUIRE(s.getDir() == dir);
                            Point newTail = s.pntAt(0);
                            Point newHead = s.pntAt(s.length() - 1);
                            REQUIRE(newTail.same(oldTail) == false);
                            REQUIRE(newHead.same(oldHead) == false);
                            REQUIRE(newHead.same(next));
                            REQUIRE(oldHead.same(s.pntAt(s.length() - 2)));
                            for(int i = 0; i < sLen; i++)
                            {
                                REQUIRE(oldTail.same(s.pntAt(i)) == false);
                            }
                        };

        Snake s(12);
        REQUIRE(s.getDir() == EAST);
        testMove(s);
        s.setDir(SOUTH);
        testMove(s);
        testMove(s);
        s.setDir(WEST);
        testMove(s);
        s.setDir(NORTH);
        testMove(s);
    }

    // Test growing the size of the snake by one point
    SECTION("snake grow test")
    {
        auto testGrow = [](Snake& s)
                        {
                            int oldLen = s.length();
                            Point next = s.getNext();
                            Point oldTail = s.pntAt(0);
                            Point oldHead = s.pntAt(oldLen - 1);
                            enum direction dir = s.getDir();
                            s.grow();
                            REQUIRE(s.getDir() == dir);
                            unsigned int newLen = s.length();
                            REQUIRE(newLen != oldLen);
                            REQUIRE(newLen == oldLen + 1);
                            Point newHead = s.pntAt(newLen - 1);
                            REQUIRE(newHead.same(oldHead) == false);
                            REQUIRE(newHead.same(next));
                            Point newTail = s.pntAt(0);
                            REQUIRE(newTail.same(oldTail));
                            Point second = s.pntAt(newLen - 2);
                            REQUIRE(oldHead.same(second));
                        };

        Snake s(9);
        REQUIRE(s.getDir() == EAST);
        testGrow(s);
        s.setDir(SOUTH);
        testGrow(s);
        testGrow(s);
        s.setDir(WEST);
        testGrow(s);
        s.setDir(NORTH);
        testGrow(s);
    }

}
