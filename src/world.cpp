#include "world.hpp"

World::World(void)
{
  b2Vec2 gravity(0.0f, -20.0f);
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
      addCircle(50+i*0.5, 50+i*20, 1.0);
    }
}

