#include "circle.hpp"
#include <cmath>

//#define PI 3.14159265
const float PI = 3.141592653589793;

Circle::Circle()
{
  radius = 1.0;
  positionX = 0.0;
  positionY = 0.0;
  velocity.direction = 0;
  velocity.speed = 0;
  
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

/**
 * Force felt by the circle.
 * @param circles Pointers to the other circles.
 * @return Force with magnitude and direction.
 */
force Circle::calcForce(std::vector <std::shared_ptr <Circle>> circles)
{
  force f;

  std::complex<float> sum (0,0);
  
  for (std::shared_ptr <Circle> circle: circles)
    {
      if (this != circle.get())
	{
	  float d = this->calcDistance(circle);
	  float r = this->calcDirection(circle);

	  sum = sum + std::polar(1/d,r);
	}
    }
  
  f.magnitude = abs(sum);
  f.direction = arg(sum);
  
  return f;
}

/**
 * Distance to another circle.
 * @param circle Pointer to the other circle.
 * @return Distance to the other circle.
 */
float Circle::calcDistance(std::shared_ptr<Circle> circle)
{
  float dx = positionX - circle->positionX;
  float dy = positionY - circle->positionY;

  float dist = sqrt(dx*dx+dy*dy);

  dist = dist - this->radius - circle->radius;
  
  return dist;
}

/**
 * Direction in which another circle is located. 
 * @param circle Pointer to the other circle.
 * @return Angle in radians pointing at the other circle is.
 */
float Circle::calcDirection(std::shared_ptr<Circle> circle)
{
  float dx = circle->positionX - positionX;
  float dy = circle->positionY - positionY;

  float angle = atan2(dy,dx);  
  
  return angle;
}

std::ostream& operator<< (std::ostream &out, const Circle &circle)
{
  out << "Circle(" << circle.radius << ", " << circle.positionX << ", " << circle.positionY << ")";
 
  return out;
}
