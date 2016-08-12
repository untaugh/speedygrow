#include "circle.hpp"
#include <cmath>

#define PI 3.14159265

Circle::Circle()
{
  radius = 10.0;
  positionX = 0.0;
  positionY = 0.0;
}

void Circle::generateVertices(int n, float * vertices)
{
  int i;

  for (i=0; i<(n*2); i++)
  {
    vertices[i*2] = cos((2*PI*i)/n) * radius + positionX;
    vertices[i*2+1] = sin((2*PI*i)/n) * radius + positionY;
  }
}
