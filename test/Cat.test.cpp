#include "criterion/criterion.hpp"
#include "../src/Cat.hpp"

Test(cat_suite, test_cat_creation) {
    // Create a Cat
    sf::Texture texture;
    Cat cat(Vector(100, 100), &texture);

    // assertions here to test Cat creation
    cr_assert_not_null(cat.getRectangle(), "Cat sprite should not be null.");
}
