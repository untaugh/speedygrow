#define CATCH_CONFIG_MAIN 
#include "catch.hpp"
#include "circle.hpp"
#include "world.hpp"

TEST_CASE("Circle class", "[circle]") {
  std::shared_ptr<Circle> c(new Circle());
  REQUIRE( c->radius == 1.0);
}

TEST_CASE("Circle physics", "[circle]")
{
  std::shared_ptr<Circle> c1(new Circle());
  std::shared_ptr<Circle> c2(new Circle());
  std::shared_ptr<Circle> c3(new Circle());

  std::vector<std::shared_ptr<Circle>> circles;

  circles.push_back(c1);
  circles.push_back(c2);
  circles.push_back(c3);
  
  c1->positionX = 0.0;
  c1->positionY = 0.0;

  c2->positionX = 3.0;
  c2->positionY = 4.0;

  c3->positionX = -2.0;
  c3->positionY = 2.0;
  
  REQUIRE(c1->calcDistance(c2) == 5.0);
  REQUIRE(c2->calcDistance(c1) == 5.0);  

  REQUIRE(c1->calcDirection(c2) == Approx(0.9273)); 
  REQUIRE(c1->calcDirection(c3) == Approx(2.3562)); 
  REQUIRE(c2->calcDirection(c1) == Approx(-2.2143));  
  REQUIRE(c3->calcDirection(c1) == Approx(-0.7854));

  //force f = c1->calcForce(circles);
  //REQUIRE( f.direction  == Approx(1.4056476493802699)); 

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
