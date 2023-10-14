#include "../src/Environment.h"
#include <iostream>

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>

using std::cout;
using std::endl;

Test(environment_suite, test_1) {
  Environment* test_env = new Environment();
  
  cr_assert(false, "Test1: X Position Wrong.");
}
