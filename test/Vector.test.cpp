#include "../src/Vector.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>

Test(vector_suite, test_1) {
  Vector vector(10, 10);
  cr_log_info("THE VECTOR X VALUE IS: %f", vector.getXPosition());

  cr_assert(vector.getXPosition() == 10, "Test1: X Position Wrong.");
  cr_assert(vector.getYPosition() == 10, "Test1: Y Position Wrong.");
}