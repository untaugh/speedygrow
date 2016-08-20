#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <Box2D/Box2D.h>

class Circle
{
public:
  Circle();
  float radius;
  float positionX;
  float positionY;

  void generateVertices(int n, float * vertices);

  //b2BodyDef bodyDef;  
  b2Body* body;
  
  friend std::ostream& operator<< (std::ostream &out, const Circle &circle);
};

#endif // CIRCLE_H
