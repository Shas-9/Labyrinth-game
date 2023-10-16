#include "../src/Environment.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>

using std::cout;
using std::endl;

Test(environment_suite, test_1) {
  cout << "TEST IS RUNNING" << endl;

  // // Tests generation of 200 random mazes
  // for (int i = 0; i < 200; i++) {
  //   Environment* test_env = new Environment();
  // }

  Environment* test_env = new Environment();

}
