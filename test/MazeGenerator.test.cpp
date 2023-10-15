#include "../src/MazeGenerator.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

Test(maze_generator_suite, test_1) {
  cout << "TEST IS RUNNING" << endl;

  MazeGenerator* generator = new MazeGenerator();
  generator->generatePaths();
}
