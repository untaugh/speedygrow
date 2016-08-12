#ifndef CIRCLE_H
#define CIRCLE_H

class Circle
{
public:
  Circle();
  float radius;
  float positionX;
  float positionY;

  void generateVertices(int n, float * vertices);
};

#endif // CIRCLE_H
