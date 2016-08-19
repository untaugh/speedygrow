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
  int i=0;

  // center of circle
  vertices[0] = positionX;
  vertices[1] = positionY;
  
  for (i=0; i<n-2; i=i+2)
    {
      vertices[i+2] = cos((2*PI*i)/(n-4)) * radius + positionX;
      vertices[i+3] = sin((2*PI*i)/(n-4)) * radius + positionY;
    }

}

std::ostream& operator<< (std::ostream &out, const Circle &circle)
{
  out << "Circle(" << circle.radius << ", " << circle.positionX << ", " << circle.positionY << ")";
 
    return out;
}
