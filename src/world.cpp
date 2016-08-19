#include "world.hpp"

World::World(void)
{

}

void World::generate(int size)
{
  circles.clear();
  
  for (int i = 0; i<size; i++)
    {
      std::shared_ptr<Circle> c(new Circle());
      c->radius = 10;
      c->positionX = 50+i*20;
      c->positionY = 50+i*20;
      circles.push_back(std::move(c));
    }
}

void World::render(void)
{
  
}
