#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "circle.hpp"
#include <Box2D/Box2D.h>

class World
{
public:
  World(void);		
  std::vector<std::shared_ptr <Circle>> circles;
  void generate(int size);
  void addCircle(float x, float y, float r);
  void update(void);
  b2World* world;
  
};

#endif // WORLD_HPP
