#include "world.hpp"

World::World(void)
{
  b2Vec2 gravity(0.0f, -1.0f);
  world = new b2World(gravity);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);

  b2Body* groundBody = world->CreateBody(&groundBodyDef);
  
  b2PolygonShape groundBox;
  groundBox.SetAsBox(200.0f, 10.0f);
  
  groundBody->CreateFixture(&groundBox, 0.0f);

}

void World::addCircle(float x, float y, float r)
{
  std::shared_ptr<Circle> c(new Circle());
  c->radius = r;
  c->positionX = x;
  c->positionY = y;

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(x, y);
  c->body = world->CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;
  fixtureDef.restitution = 0.3f;

  c->body->CreateFixture(&fixtureDef);

  circles.push_back(std::move(c));  
}

void World::generate(int size)
{
  circles.clear();
  
  for (int i = 0; i<size; i++)
    {
      addCircle(i*50, i*50, 1.0);
    }

  addCircle(20, 70, 1.0);

}

void World::update(void)
{

   for (std::shared_ptr<Circle> circle : circles)
     {
       for (std::shared_ptr<Circle> otherCircle : circles)
	 {
	   if (circle != otherCircle)
	     {

	   const b2Vec2& p1 = circle->body->GetPosition();
	   const b2Vec2& p2 = otherCircle->body->GetPosition();
	   b2Vec2 p3 = (p2-p1);

	   float d = b2Distance(p1,p2);
	   float a = b2Atan2(p3.y,p3.x);;


	   p3.Normalize();
	   p3 *= 100/d;

	   std::cout << d << " " << a <<  " " << p3.x << " " << p3.y << std::endl;

	   //b2Vec2 p4(10,10);

	   
	   circle->body->ApplyForceToCenter(p3, true);
	     }
	 }
     }
  
  int i = 0;
  for (std::shared_ptr<Circle> circle : circles)
    {
      force f = circle->calcForce(circles);

      std::complex<float> cf = std::polar(f.magnitude/10, f.direction);
      std::complex<float> cv = std::polar(circle->velocity.speed, circle->velocity.direction);

      cv = cv + cf;
      
      circle->velocity.speed = abs(cv);
      circle->velocity.direction = arg(cv);
      
      circle->positionX = circle->positionX + cv.real();
      circle->positionY = circle->positionY + cv.imag();
    }
}
