#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <Box2D/Box2D.h>
#include <complex>

struct force
{
  float magnitude;
  float direction;
};

struct velocity
{
  float speed;
  float direction;
};

struct vec2
{
  float x;
  float y;
};

class Circle
{
public:
  Circle();
  float radius;
  float positionX;
  float positionY;

  void generateVertices(int n, float * vertices);

  b2Body* body;

  struct velocity velocity;
  //std::complex<float>velocity;
  
  force calcForce(std::vector <std::shared_ptr <Circle>> circles);
  float calcDistance(std::shared_ptr<Circle> circle);
  float calcDirection(std::shared_ptr<Circle> circle);
  
  friend std::ostream& operator<< (std::ostream &out, const Circle &circle);
};

#endif // CIRCLE_H
