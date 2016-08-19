#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>

class Circle
{
public:
  Circle();
  float radius;
  float positionX;
  float positionY;

  void generateVertices(int n, float * vertices);

  friend std::ostream& operator<< (std::ostream &out, const Circle &circle);
};

#endif // CIRCLE_H
