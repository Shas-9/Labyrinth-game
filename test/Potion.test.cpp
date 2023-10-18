#include "criterion/criterion.h"
#include "../src/Potion.h"

Test(potion_suite, test_potion_creation) {
    // Create a potion
    sf::Texture texture;
    Potion potion(Vector(100, 100), &texture);

    // assertions here to test potion creation
    cr_assert_not_null(potion.getRectangle(), "Potion sprite should not be null.");
}
