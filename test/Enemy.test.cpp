#include "../src/RenderedObject.hpp"
#include "../src/Entity.hpp"
#include "../src/Enemy.hpp"
#include <criterion/criterion.h>

// test for RenderedObject and Entity also in this file
// since RenderedObject and Entity are abstract classes

// Test for RenderedObject
Test(rendered_object_suite, test_rendered_object) {
    Vector position(10, 20);
    Vector dimensions(30, 40);
    string type = "test";
    Enemy renderedObject(position, dimensions, type, 0, 0, 0, nullptr, 0, 0);

    cr_assert_eq(renderedObject.getPosition().getX(), position.getX(), "Position mismatch.");
    cr_assert_eq(renderedObject.getDimensions().getX(), dimensions.getX(), "Dimensions mismatch.");
}

// Test for Entity
Test(entity_suite, test_entity) {
    Vector position(10, 20);
    Vector dimensions(30, 40);
    string type = "test";
    int movement_speed = 5;
    int health = 100;
    int attack_damage = 10;
    Obstacle obstacles[2];
    int obstacles_num = 2;
    Enemy entity(position, dimensions, type, movement_speed, health, attack_damage, obstacles, obstacles_num, 0);

    cr_assert_eq(entity.getHealth(), health, "Health mismatch.");
    cr_assert_eq(entity.getAttackDamage(), attack_damage, "Attack damage mismatch.");
    cr_assert_eq(entity.canMove(), true, "Entity should be able to move initially.");
}

// Test for Enemy
Test(enemy_suite, test_enemy) {
    Vector position(10, 20);
    Vector dimensions(30, 40);
    string type = "test";
    int movement_speed = 5;
    int health = 100;
    int attack_damage = 10;
    Obstacle obstacles[2];
    int obstacles_num = 2;
    int sight_distance = 10;
    Enemy enemy(position, dimensions, type, movement_speed, health, attack_damage, obstacles, obstacles_num, sight_distance);

    cr_assert_eq(enemy.getHealth(), health, "Health mismatch.");
    cr_assert_eq(enemy.getAttackDamage(), attack_damage, "Attack damage mismatch.");
    cr_assert_eq(enemy.canMove(), true, "Enemy should be able to move initially.");
}