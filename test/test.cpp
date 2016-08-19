#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "circle.hpp"
#include "world.hpp"

TEST_CASE("Circle class", "[circle]") {
  Circle* c = new Circle();
  REQUIRE( c->radius == 10.0);
}

TEST_CASE("World class", "[world]")
{
  World* w = new World();
  REQUIRE(w->circles.size() == 0);
  w->generate(10);
  REQUIRE(w->circles.size() == 10);
  w->generate(100);
  REQUIRE(w->circles.size() == 100);

}
