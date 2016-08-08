#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "circle.h"

TEST_CASE("Circle class", "[circle]") {
  Circle* c = new Circle();
  REQUIRE( c->radius == 10.0);
}
