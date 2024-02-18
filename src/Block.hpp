#ifndef BLOCK_INCLUDE
#define BLOCK_INCLUDE

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include "Renderable.hpp"

class Block : public Renderable {
public:
  Block();
  Block(Vector position);
  void update();
  void printData(std::ofstream* outfile);
};

#endif