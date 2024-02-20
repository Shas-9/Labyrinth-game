#include "criterion/criterion.hpp"
#include "../src/IronSpider.hpp"

// Test the IronSpider constructor
Test(ironspider_suite, test_ironspider_creation) {
    // Create an IronSpider
    sf::Texture texture;
    IronSpider ironSpider(Vector(100, 100), nullptr, 0, &texture);

    // Add your assertions here to test IronSpider creation
    cr_assert_not_null(ironSpider.getRectangle(), "IronSpider shape should not be null.");
}
