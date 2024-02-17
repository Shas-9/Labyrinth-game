# OOP Project

## Getting started

Clone the repo and run "make all" in the terminal

## Documentation

### Loading a texture
Textures can be loaded once and used all over the codebase using a singleton design of the `TexturesHandler` wrapper class

#### How to use
First include the class:
```c++
#include "TexturesHandler.hpp"
```
Then, to get the texture see this example:
```c++
sf::Texture* texture = LOADTEXTURE("textures/stone_wall.png");
this->sprite = new sf::Sprite();
sprite->setTexture(*texture);
```

For a real example, take a look at [the Cat.cpp class](src/Cat.cpp).

### Getting a time-factor constant
A time factor constant can be obtained based on how much time passed between the current and the last frame. This can be used to adjust things like the speed of entities, etc..

#### How to use
Include file
```c++
#include "Utility.h"
```
Access time factor using:
```c++
UTIL_CLASS.getTimeFactor();
```

Real example from the [Entity.cpp class](src/Entity.cpp).
```c++
// Move the entity to new position
int factor = UTIL_CLASS.getTimeFactor();
this->position.set(this->position.getX() + (movement_speed*factor), this->position.getY());
```

## Testing

We're using the Criterion framework for testing in this project: https://github.com/Snaipe/Criterion

### Installing Criterion

To install on ubuntu run:

```bash
sudo apt-get install libcriterion-dev
```

### How to create a test

In the folder `test` create `<Class>.test.cpp` file where `<Class>` is the name of the class being tested in that file.

```bash
touch test/ExampleClass.test.cpp
```

In this file, all the testing for the class should be implemented in the following format.

```c++
#include "../src/ExampleClass.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>

// This will assess a certain functionality in the class
Test(example_class_suite, test_1) {

  cr_log_info("This is a test log: %d", 123);

  ExampleClass cls = new ExampleClass();

  // Assert conditions (must be true for the current test to pass)
  cr_assert(
    // Condition
    cls.attribute == 321,

    // Error message if condition doesn't pass
    "ERROR: The attribute 'attribute' is not 321!"
  );

  // Another assertion example
  cr_assert(cls.getNumber() == 10, "Error: Number is not 10!");
}

// This will assess another part
Test(example_class_suite, test_2) {
  // ...
}
```

For a real example check the `test/Vector.test.cpp` file.

### How to run a test file

Run the command:

```bash
make <Class>.test
```

For our example class test, we would run

```bash
make ExampleClass.test
```

### Running all tests

To run all test files execute:

```bash
make test
```

### Guide and rules for testing

- Each class will have a test file.
- Each test file will test every single method the class has.
- Each test file will test different functionalities the class should have.
- If a Class A depends on Class B through an association, the test file for Class A must test that relation.
