#include "circle.hpp"
#include <cmath>

#define PI 3.14159265

Circle::Circle()
{
  radius = 1.0;
  positionX = 0.0;
  positionY = 0.0;
  
  //bodyDef.type = b2_dynamicBody;
  //bodyDef.position.Set(positionX, positionY);
}

void Circle::generateVertices(int n, float * vertices)
{
  int i=0;

  b2Vec2 position = body->GetPosition();
  
  // center of circle
  vertices[0] = position.x;
  vertices[1] = position.y;
  
  for (i=0; i<n-2; i=i+2)
    {
      vertices[i+2] = cos((2*PI*i)/(n-4)) * radius + position.x;
      vertices[i+3] = sin((2*PI*i)/(n-4)) * radius + position.y;
    }
}

std::ostream& operator<< (std::ostream &out, const Circle &circle)
{
  out << "Circle(" << circle.radius << ", " << circle.positionX << ", " << circle.positionY << ")";
 
  return out;
}
