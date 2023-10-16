#ifndef IRON_SPIDER_INCLUDE
#define IRON_SPIDER_INCLUDE

#include "Enemy.h"
#include "Utility.h"
// #include "Weapon.h"

class IronSpider : public Enemy {
private:

public:
  IronSpider();
  IronSpider(
    Vector position,
    int movement_speed,
    int health,
    int attack_damage,
    Obstacle* obstacles,
    int sight_distance,
    sf::Texture* iron_spider_texture
  );

  // void trackPlayer();
  void update();
  void render(sf::RenderWindow *window);

  void takeDamage(int damage);
};

#endif