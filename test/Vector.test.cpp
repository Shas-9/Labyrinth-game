#include "../src/Vector.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>

// Tests whether the constructor with arguements sets attributes for the class
// The getXPosition and getYPosition should return the corresponding values
Test(vector_suite, test_1) {
  Vector vector(10, 10);

  cr_assert(vector.getX() == 10, "Test1: X Position Wrong.");
  cr_assert(vector.getY() == 10, "Test1: Y Position Wrong.");
}

// Tests whether the default constructor sets both x & y attributes to zero
Test(vector_suite, test_2) {
  Vector vector;

  cr_assert(vector.getX() == 0, "Test2: X Position Wrong.");
  cr_assert(vector.getY() == 0, "Test2: Y Position Wrong.");
}

// Tests the setPosition method
Test(vector_suite, test_3) {
  Vector vector;

  vector.set(10, 15);

  cr_assert(vector.getX() == 10, "Test3: X Position Wrong.");
  cr_assert(vector.getY() == 15, "Test3: Y Position Wrong.");
}

// Tests the moveHorizontal & moveVertical methods
Test(vector_suite, test_4) {
  Vector vector;

  vector.moveHorizontal(10);
  vector.moveVertical(15);

  cr_assert(vector.getX() == 10, "Test4: X Position Wrong.");
  cr_assert(vector.getY() == 15, "Test4: Y Position Wrong.");
}