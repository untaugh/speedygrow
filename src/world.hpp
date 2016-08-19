#ifndef WORLD_HPP
#define WORLD_HPP

#include <vector>
#include <memory>
#include "circle.hpp"

class World
{
public:
  World(void);
  std::vector<std::shared_ptr <Circle>> circles;
  void generate(int size);
  void render(void);
};

#endif // WORLD_HPP
