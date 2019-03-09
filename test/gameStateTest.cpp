// A test case for all public methods of the GameState class

// Custom class header file imports
#include "GameState.h"
#include "Point.h"

// Import testing framework
#include "catch.hpp"

TEST_CASE("gamestate test", "[gamestate]" )
{
    // Test GameState object constructor
    SECTION("gamestate init test")
    {
        auto initTest = [](const int gs, const int sl, int hs)
                        {
                            bool e = false;
                            try
                            {
                                GameState g(gs, sl, hs);
                                REQUIRE(g.playing());
                                REQUIRE(g.getGridSize() == gs);
                                REQUIRE(g.getSnakeLength() == sl);
                                REQUIRE(g.getHiscore() == hs);
                                Point food = g.getFood();
                                REQUIRE(food.getY() >= 0);
                                REQUIRE(food.getY() < gs);
                                REQUIRE(food.getX() >= 0);
                                REQUIRE(food.getX() < gs);
                            }
                            catch(...)
                            {
                                e = true;
                            }
                            if(gs <= 0 || sl <= 0 || gs < sl)
                            {
                                REQUIRE(e);
                            }
                            else
                            {
                                REQUIRE(!e);
                            }
                        };

        initTest(20, 5, 0);
        initTest(20, 19, 4);
        initTest(10, 5, 2);
        initTest(1000, 200, 0);
        initTest(0, 0, 0);
        initTest(5, 0, 0);
        initTest(0, 5, 0);
        initTest(0, 0, 5);
        initTest(5, 5, 0);
        initTest(5, 0, 5);
        initTest(0, 5, 5);
        initTest(5, 5, 5);
        initTest(-1, -1, -1);
        initTest(7, -1, -1);
        initTest(-1, 7, -1);
        initTest(-1, -1, 7);
        initTest(7, 7, -1);
        initTest(7, -1, 7);
        initTest(-1, 7, 7);
        initTest(7, 7, 7);
        initTest(-9999, -9999, -9999);
    }

    // Test pausing and resuming a game
    SECTION("gamestate pause test")
    {
        GameState g(15, 5, 0);
        REQUIRE(g.gamePaused() == false);
        g.pause();
        REQUIRE(g.gamePaused());
        g.pause();
        REQUIRE(g.gamePaused());
        g.resume();
        REQUIRE(g.gamePaused() == false);
        g.resume();
        REQUIRE(g.gamePaused() == false);
        g.pause();
        REQUIRE(g.gamePaused());
    }

    // Test getting and setting the game difficulty level
    SECTION("gamestate difficulty test")
    {
        auto testSetDif = [](GameState& g, enum difficulty d)
                          {
                              REQUIRE(g.getDifficulty() != d);
                              g.setDifficulty(d);
                              REQUIRE(g.getDifficulty() == d);
                          };

        GameState g(20, 6, -1);
        REQUIRE(g.getDifficulty() == UNDEFINED);
        testSetDif(g, HARD);
        testSetDif(g, EASY);
        testSetDif(g, BRUTAL);
        testSetDif(g, MEDIUM);
    }

    // Test getting and setting food location
    SECTION("gamestate food test")
    {
        auto testSetFood = [](GameState& g, Point p)
                           {
                               g.setFood(p);
                               Point food = g.getFood();
                               REQUIRE(food.getX() == p.getX());
                               REQUIRE(food.getY() == p.getY());
                           };

        int gridSize = 40;
        GameState g(gridSize, 23, 5);
        Point food = g.getFood();
        REQUIRE(food.getX() >= 0);
        REQUIRE(food.getX() < gridSize);
        REQUIRE(food.getY() >= 0);
        REQUIRE(food.getY() < gridSize);
        testSetFood(g, Point());
        testSetFood(g, Point(2, 5));
        testSetFood(g, Point(42, 83));
        testSetFood(g, Point(-999, 400000));
    }

    // Test setting and getting the board grid size
    SECTION("gamestate grid size test")
    {
        auto testGrid = [](int i)
                        {
                            GameState g(i, 5, 0);
                            REQUIRE(g.getGridSize() == i);
                        };

        testGrid(20);
        testGrid(30);
        testGrid(5);
        testGrid(44);
    }

    // Test setting and getting the snake's direction of travel
    SECTION("gamestate snake direction test")
    {
        auto testSetDir = [](GameState& g, enum direction d)
                          {
                              REQUIRE(g.getSnakeDir() != d);
                              g.setSnakeDir(d);
                              REQUIRE(g.getSnakeDir() == d);
                          };

        GameState g(30, 13, 99);
        REQUIRE(g.getSnakeDir() == EAST);
        testSetDir(g, NORTH);
        testSetDir(g, SOUTH);
        testSetDir(g, WEST);
        testSetDir(g, EAST);
    }

    // Test getting points out of the GameState's Snake attribute
    SECTION("gamestate get snake pnt at test")
    {
        auto snkPntAtEx = [](GameState& g, int i)
                       {
                           bool e = false;
                           try
                           {
                               g.getSnakePntAt(i);
                           }
                           catch(...)
                           {
                               e = true;
                           }
                           return e;
                       };

        int sLen = 22;
        GameState g(40, sLen, -1);
        for(int i = 0; i < sLen; i++)
        {
            REQUIRE(!snkPntAtEx(g, i));
        }
        REQUIRE(snkPntAtEx(g, -1));
        REQUIRE(snkPntAtEx(g, -25));
        REQUIRE(snkPntAtEx(g, -999));
        REQUIRE(snkPntAtEx(g, sLen));
        REQUIRE(snkPntAtEx(g, 42));
        REQUIRE(snkPntAtEx(g, 999));
    }

    // Test setting and getting the snake's starting length
    SECTION("gamestate snake st length test")
    {
        auto stLenTest = [](int i)
                          {
                              GameState g(40, i, 0);
                              REQUIRE(g.getSnakeStLen() == i);
                          };

        stLenTest(2);
        stLenTest(22);
        stLenTest(8);
        stLenTest(1);
    }

    // Test quitting the game
    SECTION("gamestate quit test")
    {
        GameState g(40, 20, 10);
        REQUIRE(g.playing());
        REQUIRE(g.playing());
        g.quit();
        REQUIRE(g.playing() == false);
        g.quit();
        REQUIRE(g.playing() == false);
    }

    // Test changing and resetting the game state
    SECTION("gamestate reset test")
    {
        int gridSize = 30;
        int snakeLen = 10;
        int hiscore = 22;
        GameState g(gridSize, snakeLen, hiscore);
        REQUIRE(g.getGridSize() == gridSize);
        REQUIRE(g.getSnakeLength() == snakeLen);
        REQUIRE(g.getHiscore() == hiscore);
        REQUIRE(g.playing() == true);
        REQUIRE(g.gamePaused() == false);
        REQUIRE(g.getDifficulty() == UNDEFINED);
        g.quit();
        REQUIRE(g.playing() == false);
        g.pause();
        REQUIRE(g.playing() == false);
        REQUIRE(g.gamePaused() == true);
        g.setDifficulty(BRUTAL);
        REQUIRE(g.playing() == false);
        REQUIRE(g.gamePaused() == true);
        REQUIRE(g.getDifficulty() == BRUTAL);
        g.setFood(Point(-999, -998));
        Point food = g.getFood();
        REQUIRE(g.playing() == false);
        REQUIRE(g.gamePaused() == true);
        REQUIRE(g.getDifficulty() == BRUTAL);
        REQUIRE(food.getX() == -999);
        REQUIRE(food.getY() == -998);
        g.reset();
        REQUIRE(g.getGridSize() == gridSize);
        REQUIRE(g.getSnakeLength() == snakeLen);
        REQUIRE(g.getHiscore() == hiscore);
        REQUIRE(g.playing() == true);
        REQUIRE(g.gamePaused() == false);
        REQUIRE(g.getDifficulty() == UNDEFINED);
        food = g.getFood();
        REQUIRE(food.getX() >= 0);
        REQUIRE(food.getX() < gridSize);
        REQUIRE(food.getY() >= 0);
        REQUIRE(food.getY() < gridSize);
    }

    // Test all variations on moving the snake
    SECTION("gamestate move snake test")
    {
        GameState g(50, 5, 102);

        // Test moving snake east
        SECTION("gamestate move snake east test")
        {
            g.setFood(Point(-999, -999));
            REQUIRE(g.getSnakeDir() == EAST);
            Point oldHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            Point newHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            REQUIRE(newHead.getX() == oldHead.getX() + 1);
        }

        // Test moving snake south
        SECTION("gamestate move snake south test")
        {
            g.reset();
            g.setFood(Point(-999, -999));
            Point oldHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            g.setSnakeDir(SOUTH);
            REQUIRE(g.getSnakeDir() == SOUTH);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            Point newHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            REQUIRE(newHead.getY() == oldHead.getY() + 1);
        }

        // Test moving snake north
        SECTION("gamestate move snake north test")
        {
            g.reset();
            g.setFood(Point(-999, -999));
            Point oldHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            g.setSnakeDir(NORTH);
            REQUIRE(g.getSnakeDir() == NORTH);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            Point newHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            REQUIRE(newHead.getY() == oldHead.getY() - 1);
        }

        // Test moving snake west
        SECTION("gamestate move snake west test")
        {
            g.reset();
            g.setFood(Point(-999, -999));
            g.setSnakeDir(SOUTH);
            g.moveSnake();
            Point oldHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            g.setSnakeDir(WEST);
            REQUIRE(g.getSnakeDir() == WEST);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            Point newHead = g.getSnakePntAt(g.getSnakeLength() - 1);
            REQUIRE(newHead.getX() == oldHead.getX() - 1);
        }

        // Test colliding with each of the board walls
        SECTION("wall collision test")
        {
            auto hitWall = [](GameState& g,
                              std::function<bool(GameState&)> atWall)
                           {
                               g.setFood(Point(-999, -999));
                               int cnt = 0;
                               int gridSize = g.getGridSize();
                               int lastI = g.getSnakeLength() - 1;
                               while(!atWall(g))
                               {
                                   // Bail out if infinite loop suspected
                                   REQUIRE(cnt < gridSize);
                                   // Otherwise:
                                   g.moveSnake();
                                   REQUIRE(g.snakeAlive());
                                   cnt++;
                               }
                               Point oldHead = g.getSnakePntAt(lastI);
                               g.moveSnake();
                               Point newHead = g.getSnakePntAt(lastI);
                               REQUIRE(newHead.same(oldHead));
                               REQUIRE(g.snakeAlive() == false);
                           };

            // Test colliding with the eastern wall
            SECTION("east wall collision test")
            {
                g.reset();
                REQUIRE(g.getSnakeDir() == EAST);
                auto atWall = [](GameState& g)
                              {
                                  int lastI = g.getSnakeLength() - 1;
                                  Point head = g.getSnakePntAt(lastI);
                                  if(head.getX() == g.getGridSize() - 1)
                                  {
                                      return true;
                                  }
                                  return false;
                              };
                hitWall(g, atWall);
            }

            // Test colliding with the southern wall
            SECTION("south wall collision test")
            {
                g.reset();
                g.setSnakeDir(SOUTH);
                auto atWall = [](GameState& g)
                              {
                                  int lastI = g.getSnakeLength() - 1;
                                  Point head = g.getSnakePntAt(lastI);
                                  if(head.getY() == g.getGridSize() - 1)
                                  {
                                      return true;
                                  }
                                  return false;
                              };
                hitWall(g, atWall);
            }

            // Test colliding with the northern wall
            SECTION("north wall collision test")
            {
                g.reset();
                g.setSnakeDir(NORTH);
                auto atWall = [](GameState& g)
                              {
                                  int lastI = g.getSnakeLength() - 1;
                                  Point head = g.getSnakePntAt(lastI);
                                  if(head.getY() == 0)
                                  {
                                      return true;
                                  }
                                  return false;
                              };
                hitWall(g, atWall);
            }

            // Test colliding with the western wall
            SECTION("west wall collision test")
            {
                g.reset();
                g.setFood(Point(-999, -999));
                g.setSnakeDir(SOUTH);
                g.moveSnake();
                g.setSnakeDir(WEST);
                auto atWall = [](GameState& g)
                              {
                                  int lastI = g.getSnakeLength() - 1;
                                  Point head = g.getSnakePntAt(lastI);
                                  if(head.getX() == 0)
                                  {
                                      return true;
                                  }
                                  return false;
                              };
                hitWall(g, atWall);
            }

        }

        // Test crashing the snake into its own body
        SECTION("gamestate body collision test")
        {
            g.reset();
            g.setFood(Point(-999, -999));
            REQUIRE(g.snakeAlive());
            g.setSnakeDir(SOUTH);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            g.setSnakeDir(WEST);
            g.moveSnake();
            REQUIRE(g.snakeAlive());
            g.setSnakeDir(NORTH);
            g.moveSnake();
            REQUIRE(g.snakeAlive() == false);
        }

        // Test getting the snake to eat some food
        SECTION("gamestate food collision test")
        {
            g.reset();
            REQUIRE(g.getSnakeDir() == EAST);
            Point head = g.getSnakePntAt(g.getSnakeLength() - 1);
            Point next(head.getX() + 1, head.getY());
            g.setFood(next);
            REQUIRE(g.getSnakeLength() == g.getSnakeStLen());
            REQUIRE(g.getScore() == 0);
            g.moveSnake();
            REQUIRE(g.getSnakeLength() == g.getSnakeStLen() + 1);
            REQUIRE(g.getScore() == 1);
            REQUIRE(g.snakeAlive());
        }
    }

    // Test getting and setting the hiscore
    SECTION("gamestate hiscore test")
    {
        auto testHiscoreInit = [](int i)
                               {
                                  GameState g(20, 5, i);
                                  REQUIRE(g.getHiscore() == i);
                               };

        auto testHiscoreInc = [](int stHiscore)
                              {
                                  GameState g(50, 5, stHiscore);
                                  REQUIRE(g.getSnakeDir() == EAST);
                                  int lastI = g.getSnakeLength() - 1;
                                  Point head = g.getSnakePntAt(lastI);
                                  Point next(head.getX() + 1, head.getY());
                                  g.setFood(next);
                                  g.moveSnake();
                                  int max = stHiscore > 1 ? stHiscore : 1;
                                  REQUIRE(g.getHiscore() == max);
                              };

        testHiscoreInit(5);
        testHiscoreInit(42);
        testHiscoreInit(0);
        testHiscoreInit(-1);
        testHiscoreInit(-999);
        testHiscoreInit(88888);
        testHiscoreInc(0);
        testHiscoreInc(-1);
        testHiscoreInc(-999);
        testHiscoreInc(42);
        testHiscoreInc(7000);
    }

    // Test incrementing and getting the score
    SECTION("gamestate score test")
    {
        auto testScoreInc = [](GameState& g)
                            {
                                int sc = g.getScore();
                                REQUIRE(g.getSnakeDir() == EAST);
                                int lastI = g.getSnakeLength() - 1;
                                Point head = g.getSnakePntAt(lastI);
                                Point next(head.getX() + 1, head.getY());
                                g.setFood(next);
                                g.moveSnake();
                                REQUIRE(g.getScore() == sc + 1);
                            };

        GameState g(20, 5, 33);
        REQUIRE(g.getScore() == 0);
        for(int i = 0; i < 8; i++)
        {
            testScoreInc(g);
        }
    }

    // Test setting, getting, and incrementing the snake's length
    SECTION("gamestate snake length test")
    {
        auto testLenInit = [](int i)
                           {
                               GameState g(40, i, 0);
                               REQUIRE(g.getSnakeLength() == i);
                           };

        auto testLenInc = [](GameState& g)
                          {
                              int sl = g.getSnakeLength();
                              REQUIRE(g.getSnakeDir() == EAST);
                              int lastI = g.getSnakeLength() - 1;
                              Point head = g.getSnakePntAt(lastI);
                              Point next(head.getX() + 1, head.getY());
                              g.setFood(next);
                              g.moveSnake();
                              REQUIRE(g.getSnakeLength() == sl + 1);
                          };

        testLenInit(2);
        testLenInit(22);
        testLenInit(8);
        testLenInit(1);
        GameState g(50, 3, 44);
        for(int i = 0; i < 8; i++)
        {
            testLenInc(g);
        }
    }

}
